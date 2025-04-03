
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFShop.generated.h"

USTRUCT(BlueprintType)
struct FShopItem
{
    GENERATED_BODY()

public:
    // 아이템 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    FString Name;

    // 아이템 가격
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    int32 Price;

    FShopItem()
        : Name(TEXT("")), Price(0)
    {
    }

    FShopItem(const FString& InName, int32 InPrice)
        : Name(InName), Price(InPrice)
    {
    }
};


UCLASS()
class GLADIATORSFANTASY_API UGFShop : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // 위젯 초기화 함수 (예: 로비에서 호출)
    UFUNCTION(BlueprintCallable, Category = "Shop")
    void InitializeShop();

    // 특정 아이템을 구매하는 함수 (버튼 클릭 등에서 호출)
    UFUNCTION(BlueprintCallable, Category = "Shop")
    void OnBuyItem(int32 ItemIndex);

    //플레이어가 상점에 판매하는 함수
    UFUNCTION(BlueprintCallable, Category = "Shop")
    bool SellItem(int32 InventoryIndex, class AGFBaseCharacter* Seller);

    // 상점 아이템 목록 (Blueprint에서도 수정 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    TArray<FShopItem> ShopItems;

    // 플레이어가 보유한 골드 (UI에서 표시 가능)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    int32 PlayerGold;

protected:
    // 상점 아이템 데이터를 초기화하는 함수
    void LoadShopItems();

    // 상점 UI 갱신 이벤트
    UFUNCTION(BlueprintImplementableEvent, Category = "Shop")
    void UpdateShopUI();
};
