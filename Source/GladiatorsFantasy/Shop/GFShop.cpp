
#include "Shop/GFShop.h"
#include "Character/GFBaseCharacter.h"
#include "Engine/Engine.h"
#include "GameInstance/GFGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Server/GFBasePlayerState.h"

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

    // 상점 아이템 데이터 로드
    LoadShopItems();

    // UI 갱신 (Blueprint에서 구현된 UpdateShopUI 이벤트가 호출)
    UpdateShopUI();
}

FString UGFShop::LoadShopItems()
{
    // 기존 아이템 목록 초기화
    ShopItems.Empty();
    ShopItems.Add(FShopItem(TEXT("BasicSword"), 100));
    ShopItems.Add(FShopItem(TEXT("Bow"), 100));
    ShopItems.Add(FShopItem(TEXT("DoubleHandedSword"), 100));
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

    UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    if (!GI)
    {
        UE_LOG(LogTemp, Warning, TEXT("GameInstance를 찾을 수 없습니다."));
        return;
    }

    FShopItem& Item = ShopItems[ItemIndex];

    FString PlayerId = GetOwningPlayerId(); // 플레이어 이름을 가져오는 방식 필요

    if (GI->PlayerDataMap.Contains(PlayerId))
    {
        FPlayerData& Data = GI->PlayerDataMap[PlayerId];

        if (Data.Money >= Item.Price)
        {
            Data.Money -= Item.Price;
            PlayerGold = Data.Money;

            UE_LOG(LogTemp, Log, TEXT("아이템 [%s]을(를) 구매했습니다. 남은 돈: %d"), *Item.Name, Data.Money);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, Data.Money);
        }
        // 구매 후 UI 갱신
        UpdateShopUI();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어 정보를 찾을 수 없습니다. 이름: %s"), *PlayerId);
    }
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

