
#include "Shop/GFShop.h"
#include "Character/GFBaseCharacter.h"
#include "Engine/Engine.h"
#include "GameInstance/GFGameInstance.h"
#include "GameFramework/PlayerState.h"
#include "Server/GFBasePlayerState.h"
#include "Server/GFStorePlayerController.h"

void UGFShop::CompleteShopSelection()
{
    // 상점 선택 완료 시 플레이어 컨트롤러 캐스팅 후 bIsReady 설정
    AGFStorePlayerController* PC = Cast<AGFStorePlayerController>(GetOwningPlayer());
    if (PC)
    {
        PC->ServerSetReady(true);
        UE_LOG(LogTemp, Log, TEXT("플레이어의 bIsReady 상태를 true로 설정했습니다."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("플레이어의 컨트롤러가 유효하지 않습니다."));
    }

    UpdateShopUI();

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

        UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
        if (!GI)
        {
            UE_LOG(LogTemp, Warning, TEXT("GameInstance를 찾을 수 없습니다."));
            return;
        }

        // 현재 스테이지 인덱스 가져오기
        int32 CurrentStage = GI->GetLevelIndex();

        // 해당 스테이지의 구매 여부 체크
        if (GI->StagePurchaseStatus.IsValidIndex(CurrentStage) && GI->StagePurchaseStatus[CurrentStage])
        {
            UE_LOG(LogTemp, Warning, TEXT("현재 스테이지에서는 이미 구매하였습니다."));
            return;
        }

        const FString PlayerKey = TEXT("DummyKey");  // 사용 중인 키

        if (!GI->PlayerDataMap.Contains(PlayerKey))
        {
            UE_LOG(LogTemp, Warning, TEXT("PlayerDataMap에 %s 키가 없습니다."), *PlayerKey);
            return;
        }

        FPlayerData& Data = GI->PlayerDataMap[PlayerKey];
        const FShopItem& Item = ShopItems[ItemIndex];

        if (Data.Money >= Item.Price)
        {
            Data.Money -= Item.Price;
            PlayerGold = Data.Money; // Shop 내 PlayerGold 변수에도 동기화

            // 구매 성공 시 현재 스테이지의 구매 상태를 true로 설정
            GI->StagePurchaseStatus[CurrentStage] = true;

            UE_LOG(LogTemp, Log, TEXT("아이템 [%s]을(를) 구매했습니다. 남은 돈: %d"), *Item.Name, Data.Money);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("골드가 부족합니다. [%s] 가격: %d, 현재 돈: %d"), *Item.Name, Item.Price, Data.Money);
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

