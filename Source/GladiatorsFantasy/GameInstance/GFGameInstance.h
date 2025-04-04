
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GFGameInstance.generated.h"

class AGF_FFAGameState;
class AGF_FFAPlayerState;

// 승리 및 패배 수를 기록하기 위한 구조체
USTRUCT(BlueprintType)
struct FWinLossRecord
{
    GENERATED_BODY()

public:
    // 승리 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 WinCount;

    // 패배 수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LossCount;

    FWinLossRecord()
        : WinCount(0), LossCount(0)
    {
    }
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

    // 게임 상태 변경 및 조회 함수
    UFUNCTION(BlueprintCallable, Category = "State")
    void SetGameState(EGameState NewState);

    UFUNCTION(BlueprintCallable, Category = "State")
    EGameState GetGameState() const;

    // 통계 관련 변수들
    //플레이어 킬수 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TMap<FString, int32> PlayerKillCounts;

    //플레이어별 킬수 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpdatePlayerKillCounts(const TArray<AGF_FFAPlayerState*>& PlayerStates);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetTotalKillCount() const;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FWinLossRecord WinLossRecord;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LevelIndex;

    // 통계 업데이트 및 조회용 함수들

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddWin();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddLoss();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetLevelIndex(int32 NewLevelIndex);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    FWinLossRecord GetWinLossRecord() const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetLevelIndex() const;

    // Top Killers 저장
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    TArray<TObjectPtr<AGF_FFAPlayerState>> TopKillers;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetTopKillers(const TArray<AGF_FFAPlayerState*>& InTopKillers);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    TArray<AGF_FFAPlayerState*> GetTopKillersFromInstance() const;

    //돈
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 PlayerMoney;

private:
    // 현재 게임 상태 저장 변수
    EGameState CurrentGameState;
};
