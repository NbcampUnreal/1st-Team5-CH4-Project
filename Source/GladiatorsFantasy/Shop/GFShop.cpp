
#include "Shop/GFShop.h"
#include "Character/GFBaseCharacter.h"
#include "Engine/Engine.h"
#include "GameInstance/GFGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Server/GFBasePlayerState.h"
#include "Server/GFStorePlayerController.h"
#include "Server/GFStorePlayerState.h"
#include "Weapon/GFWeaponBase.h"
#include "Math/UnrealMathUtility.h"

void UGFShop::CompleteShopSelection()
{
    // 상점 선택 완료 시 플레이어 컨트롤러 캐스팅 후 bIsReady 설정
    AGFStorePlayerController* PC = Cast<AGFStorePlayerController>(GetOwningPlayer());
    if (PC)
    {
        APlayerState* BasePS = PC->PlayerState;
        if (BasePS)
        {
            AGFStorePlayerState* PS = Cast<AGFStorePlayerState>(BasePS);
            if (PS)
            {

                PS->SetIsReady(true);

            }
            else
            {
                UE_LOG(LogTemp, Warning,
                    TEXT("PlayerState가 AGFStorePlayerState 타입으로 캐스팅되지 않았습니다."));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning,
                TEXT("플레이어의 PlayerState가 유효하지 않습니다."));
        }

        PC->ServerSetReady(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("플레이어의 컨트롤러가 유효하지 않습니다."));
    }

}

void UGFShop::InitializeShop()
{
    APlayerController* PC = GetOwningPlayer();

    if (PC && PC->PlayerState)
    {
        // PlayerState가 우리가 원하는 타입(예: AGFBasePlayerState)으로 캐스팅 가능한지 확인
        AGFBasePlayerState* BPS = Cast<AGFBasePlayerState>(PC->PlayerState);
        if (BPS)
        {
            // PlayerState에 저장된 돈 값으로 PlayerGold 동기화
            PlayerGold = BPS->GetMoney();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("PlayerState가 AGFBasePlayerState로 캐스팅되지 않았습니다."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어 컨트롤러 또는 PlayerState를 찾을 수 없습니다."));
    }


    // 상점 아이템 데이터 로드
    LoadShopItems();

    // UI 갱신 (Blueprint에서 구현된 UpdateShopUI 이벤트가 호출)
    UpdateShopUI();
}

void UGFShop::RandomizeItemRarity(int32 Index)
{
    // 인덱스 유효성 체크
    if (!ShopItems.IsValidIndex(Index))
    {
        UE_LOG(LogTemp, Warning, TEXT("잘못된 ShopItem 인덱스입니다."));
        return;
    }

    // EWeaponRarity의 유효 범위 (EWR_Max는 최대값 표시용이므로 제외)
    int32 RarityRange = static_cast<int32>(EWeaponRarity::EWR_Max) - 1;
    // FRandomStream 사용: 매 호출 시 새로운 시드 생성
    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    // 0부터 RarityRange (포함)까지의 무작위 정수 생성
    int32 RandomIndex = RandomStream.RandRange(0, RarityRange);
    EWeaponRarity RandomRarity = static_cast<EWeaponRarity>(RandomIndex);

    // 기존 Setter를 사용하여 해당 인덱스의 Rarity 변경
    SetItemRarity(Index, RandomRarity);

    UE_LOG(LogTemp, Log, TEXT("RandomizeItemRarity: 인덱스[%d]의 무기 등급을 %d로 설정했습니다."), Index, RandomIndex);
}

void UGFShop::SetItemRarity(int32 Index, EWeaponRarity NewRarity)
{
    if (ShopItems.IsValidIndex(Index))
    {
        ShopItems[Index].Rarity = NewRarity;
        
        UpdateShopUI();
        UE_LOG(LogTemp, Log, TEXT("ShopItem [%d] Rarity 변경: %d"), Index, static_cast<int32>(NewRarity));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("잘못된 ShopItem 인덱스입니다."));
    }
}

EWeaponRarity UGFShop::GetItemRarity(int32 Index) const
{
    if (ShopItems.IsValidIndex(Index))
    {
        return ShopItems[Index].Rarity;
    }
    return EWeaponRarity::EWR_Nomal;
}

FShopItem CreateRandomizedShopItem(const FString& ItemName, int32 Price)
{
    // EWeaponRarity의 유효 범위: EWR_Nomal부터 EWR_Legend까지
    int32 RarityRange = static_cast<int32>(EWeaponRarity::EWR_Max) - 1;

    FRandomStream RandomStream;
    RandomStream.GenerateNewSeed();

    // 0부터 (RarityRange - 1)까지 무작위 정수 생성
    int32 RandomIndex = RandomStream.RandRange(0, RarityRange);
    EWeaponRarity RandomRarity = static_cast<EWeaponRarity>(RandomIndex);

    return FShopItem(ItemName, Price, RandomRarity);
}

FString UGFShop::LoadShopItems()
{
    // 기존 아이템 목록 초기화
    ShopItems.Empty();

    ShopItems.Add(FShopItem(TEXT("BasicSword"), 100));
    ShopItems.Add(FShopItem(TEXT("Bow"), 100));
    ShopItems.Add(FShopItem(TEXT("DoubleHandedSword"), 100, EWeaponRarity::EWR_Legend));
    ShopItems.Add(FShopItem(TEXT("MagicBook"), 100));

    UpdateShopUI();

    return ShopItems.Num() > 0 ? ShopItems[0].Name : FString("");
}

void UGFShop::OnBuyItem(int32 ItemIndex)
{
    if (!ShopItems.IsValidIndex(ItemIndex))
    {
        UE_LOG(LogTemp, Warning, TEXT("잘못된 아이템 인덱스입니다."));
        return;
    }

    AGFStorePlayerController* PC = Cast<AGFStorePlayerController>(GetOwningPlayer());
    if (!PC)
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어 컨트롤러를 찾을 수 없습니다."));
        return;
    }

    APlayerState* BasePS = PC->PlayerState;
    if (!BasePS)
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어의 PlayerState가 유효하지 않습니다."));
        return;
    }

    AGFStorePlayerState* StorePS = Cast<AGFStorePlayerState>(BasePS);
    if (!StorePS)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerState가 AGFStorePlayerState 타입으로 캐스팅되지 않았습니다."));
        return;
    }

    int32 CurrentMoney = StorePS->GetMoney();
    const FShopItem& Item = ShopItems[ItemIndex];

    UE_LOG(LogTemp, Log, TEXT("구매 전: CurrentMoney = %d, Item.Price = %d"), CurrentMoney, Item.Price);

    if (CurrentMoney >= Item.Price)
    {
        StorePS->SetMoney(CurrentMoney - Item.Price);
        PlayerGold = StorePS->GetMoney();

        UE_LOG(LogTemp, Log, TEXT("아이템 [%s] 구매 성공, 남은 돈: %d"), *Item.Name, StorePS->GetMoney());

        // 구매 성공 시 무기 정보 업데이트 등
        StorePS->SetFWeaponInfo(Item.Name, Item.Rarity);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, CurrentMoney);
    }
    UpdateShopUI();
}

bool UGFShop::SellItem(int32 InventoryIndex, AGFBaseCharacter* Seller)
{
    if (!Seller)
    {
        UE_LOG(LogTemp, Warning, TEXT("판매자(Seller)가 유효하지 않습니다."));
        return false;
    }

    // 판매 후 UI 갱신
    UpdateShopUI();

    return true;
}

FString UGFShop::GetOwningPlayerId() const
{
    APlayerController* PC = GetOwningPlayer();
    if (PC)
    {
        APlayerState* PS = PC->PlayerState;
        if (PS)
        {
            AGFBasePlayerState* BPS = Cast<AGFBasePlayerState>(PS);
            if (BPS)
            {
                return BPS->GetPlayerUniqueId();
            }
            
        }
    }
    return TEXT("Unknown");
}

