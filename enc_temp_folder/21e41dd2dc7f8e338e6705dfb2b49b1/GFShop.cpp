
#include "Shop/GFShop.h"
#include "Character/GFBaseCharacter.h"
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

FString UGFShop::LoadShopItems()
{
    TArray<FShopItem> AllItems;
    AllItems.Add(FShopItem(TEXT("BasicSword"), 100));
    AllItems.Add(FShopItem(TEXT("Bow"), 100));
    AllItems.Add(FShopItem(TEXT("DoubleHandedSword"), 100));
    AllItems.Add(FShopItem(TEXT("MagicBook"), 120));

    // 기존 아이템 목록 초기화
    ShopItems.Empty();

    int32 NumToSelect = 4;
    TArray<FShopItem> TempPool = AllItems;

    for (int32 i = 0; i < AllItems.Num(); i++)
    {
        ShopItems.Add(AllItems[i]);
    }

    UpdateShopUI();

    // 첫 번째 아이템의 이름을 반환 (WeaponName으로 사용)
    if (ShopItems.Num() > 0)
    {
        return ShopItems[0].Name;
    }
    return FString("");
}

void UGFShop::OnBuyItem(int32 ItemIndex)
{
    if (ShopItems.IsValidIndex(ItemIndex))
    {
        FShopItem& Item = ShopItems[ItemIndex];
        if (PlayerGold >= Item.Price)
        {
            // 골드 차감 및 구매 처리 (인벤토리 추가 등 추가 로직 필요)
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