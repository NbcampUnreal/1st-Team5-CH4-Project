
#include "Shop/GFShop.h"
#include "Character/GFBaseCharacter.h"
#include "Engine/Engine.h"
#include "GameInstance/GFGameInstance.h"

void UGFShop::InitializeShop()
{
    // 초기 플레이어 골드 설정
    UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    if (GI)
    {
        GI->PlayerMoney = 1000;
        PlayerGold = GI->PlayerMoney; // 동기화
    }

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

    if (GI->PlayerMoney >= Item.Price)
    {
        GI->PlayerMoney -= Item.Price;
        PlayerGold = GI->PlayerMoney; // 동기화

        UE_LOG(LogTemp, Log, TEXT("아이템 [%s]을(를) 구매했습니다. 남은 돈: %d"), *Item.Name, GI->PlayerMoney);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, GI->PlayerMoney);
    }
        // 구매 후 UI 갱신
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