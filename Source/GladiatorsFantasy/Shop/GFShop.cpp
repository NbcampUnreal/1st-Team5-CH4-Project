
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
    //// 플레이어 ID 가져옴
    //FString PlayerId = GetOwningPlayerId();

    //// 초기 플레이어 골드 설정
    //UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    //if (GI)
    //{
    //    GI->PlayerDataMap[PlayerId].Money = 1000;
    //    PlayerGold = GI->PlayerDataMap[PlayerId].Money; // 동기화
    //}

    //임시코드
    FString PlayerId = GetOwningPlayerId();
    UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    if (GI)
    {
        // 이미 데이터가 존재한다면 골드 초기화를 하지 않음
        if (!GI->PlayerDataMap.Contains(PlayerId))
        {
            FPlayerData NewPlayerData;
            NewPlayerData.PlayerCustomName = PlayerId;
            NewPlayerData.Money = 1000; // 최초 초기화 시에만 설정
            NewPlayerData.WinPoint = 0;
            NewPlayerData.LossCount = 0;
            GI->PlayerDataMap.Add(PlayerId, NewPlayerData);
        }
        // 현재 상점 위젯의 플레이어 골드 동기화
        PlayerGold = GI->PlayerDataMap[PlayerId].Money;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameInstance를 찾을 수 없습니다."));
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
    //if (!ShopItems.IsValidIndex(ItemIndex))
    //{
        //UE_LOG(LogTemp, Warning, TEXT("잘못된 아이템 인덱스입니다."));
        //return;
    //}

    //UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    //if (!GI)
    //{
        //UE_LOG(LogTemp, Warning, TEXT("GameInstance를 찾을 수 없습니다."));
        //return;
    //}

    //FShopItem& Item = ShopItems[ItemIndex];

    //FString PlayerId = GetOwningPlayerId(); // 플레이어 이름을 가져오는 방식 필요

    //if (GI->PlayerDataMap.Contains(PlayerId))
    //{
        //FPlayerData& Data = GI->PlayerDataMap[PlayerId];

        //if (Data.Money >= Item.Price)
        //{
            //Data.Money -= Item.Price;
            //PlayerGold = Data.Money;

            //UE_LOG(LogTemp, Log, TEXT("아이템 [%s]을(를) 구매했습니다. 남은 돈: %d"), *Item.Name, Data.Money);
        //}
        //else
        //{
            //UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, Data.Money);
        //}
        

        // 아이템 인덱스 유효성 체크
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

        UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
        if (GI)
        {
            int32 CurrentStage = GI->GetLevelIndex();
            if (GI->StagePurchaseStatus.IsValidIndex(CurrentStage) && GI->StagePurchaseStatus[CurrentStage])
            {
                UE_LOG(LogTemp, Warning, TEXT("현재 스테이지에서는 이미 구매하였습니다."));
                return;
            }
        }

        // 플레이어의 돈을 PlayerState에서 가져와 비교
        int32 CurrentMoney = StorePS->GetMoney();
        const FShopItem& Item = ShopItems[ItemIndex];

        if (CurrentMoney >= Item.Price)
        {
            // 아이템 가격만큼 돈 차감
            StorePS->SetMoney(CurrentMoney - Item.Price);
            // UI 갱신을 위해 로컬 변수도 업데이트
            PlayerGold = StorePS->GetMoney();

            UE_LOG(LogTemp, Log, TEXT("아이템 [%s]을(를) 구매했습니다. 남은 돈: %d"), *Item.Name, StorePS->GetMoney());

            // 구매 성공 시 WeaponInfo 업데이트
            StorePS->SetFWeaponInfo(Item.Name, Item.Rarity);

            // 구매 성공 시 현재 스테이지 상태를 true로 설정
            if (GI)
            {
                int32 CurrentStage = GI->GetLevelIndex();
                if (GI->StagePurchaseStatus.IsValidIndex(CurrentStage))
                {
                    GI->StagePurchaseStatus[CurrentStage] = true;
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, CurrentMoney);
        }


        // 구매 후 UI 갱신
        UpdateShopUI();
    //else
    //{
        //UE_LOG(LogTemp, Warning, TEXT("플레이어 정보를 찾을 수 없습니다. 이름: %s"), *PlayerId);
    //}
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

