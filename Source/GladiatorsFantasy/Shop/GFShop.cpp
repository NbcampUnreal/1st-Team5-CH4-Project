
#include "Shop/GFShop.h"
#include "Engine/Engine.h"

void UGFShop::InitializeShop()
{
    // 초기 플레이어 골드 설정
    PlayerGold = 1000;

    // 상점 아이템 데이터 로드
    LoadShopItems();

    // UI 갱신 (Blueprint에서 구현된 UpdateShopUI 이벤트가 호출)
    UpdateShopUI();
}

void UGFShop::LoadShopItems()
{
    // 기존 아이템 목록 초기화
    ShopItems.Empty();

    ShopItems.Add(FShopItem(TEXT("Iron Sword"), 500));
    ShopItems.Add(FShopItem(TEXT("Leather Armor"), 500));
}

void UGFShop::OnBuyItem(int32 ItemIndex)
{
    if (ShopItems.IsValidIndex(ItemIndex))
    {
        FShopItem& Item = ShopItems[ItemIndex];
        if (PlayerGold >= Item.Price)
        {
            // 골드 차감 및 구매 처리 (실제 프로젝트에서는 인벤토리 추가 등 추가 로직 필요)
            PlayerGold -= Item.Price;
            UE_LOG(LogTemp, Log, TEXT("아이템 [%s] 을(를) 구매했습니다."), *Item.Name);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다: [%s]"), *Item.Name);
        }
        // 구매 후 UI 갱신
        UpdateShopUI();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("잘못된 아이템 인덱스입니다."));
    }
}