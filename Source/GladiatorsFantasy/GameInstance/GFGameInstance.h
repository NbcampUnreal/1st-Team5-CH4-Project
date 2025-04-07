
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GFGameInstance.generated.h"

class AGF_FFAGameState;
class AGFBasePlayerState;
class AGF_FFAPlayerState;

// Player의 정보 저장
USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerCustomName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Money;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WinPoint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LossCount;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite)
    //FWeaponInfo WeaponInfo; // 이 구조체도 정의 필요!!!!
};

// 게임 상태를 정의하는 enum
UENUM(BlueprintType)
enum class EGameState : uint8
{
    EGS_MainMenu   UMETA(DisplayName = "Main Menu"),
    EGS_InGame     UMETA(DisplayName = "In Game"),
    EGS_GameOver   UMETA(DisplayName = "Game Over")
};

UCLASS()
class GLADIATORSFANTASY_API UGFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    // 초기화 시 호출되는 함수
    virtual void Init() override;

    // Player 전체 정보 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    TMap<FString, FPlayerData> PlayerDataMap;

    // 통계 관련 변수들
    //플레이어 킬수 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TMap<FString, int32> PlayerKillCounts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LevelIndex;

    // Top Killers 저장
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    TArray<TObjectPtr<AGF_FFAPlayerState>> TopKillers;

    // 게임 상태 변경 및 조회 함수
    UFUNCTION(BlueprintCallable, Category = "State")
    void SetGameState(EGameState NewState);

    UFUNCTION(BlueprintCallable, Category = "State")
    EGameState GetGameState() const;

    //플레이어별 킬수 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpdatePlayerKillCounts(const TArray<AGF_FFAPlayerState*>& PlayerStates);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetTotalKillCount() const;

    // 통계 업데이트 및 조회용 함수들

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddWin(const FString& PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddLoss(const FString& PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetLevelIndex(int32 NewLevelIndex);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetLevelIndex() const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetTopKillers(const TArray<AGF_FFAPlayerState*>& InTopKillers);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    TArray<AGF_FFAPlayerState*> GetTopKillersFromInstance() const;

    // 각 스테이지별 구매 여부 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    TArray<bool> StagePurchaseStatus;

private:
    // 현재 게임 상태 저장 변수
    EGameState CurrentGameState;
};
