
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GFGameInstance.generated.h"

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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 KillCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FWinLossRecord WinLossRecord;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LevelIndex;

    // 통계 업데이트 및 조회용 함수들
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddKillCount(int32 Kills);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddWin();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddLoss();

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetLevelIndex(int32 NewLevelIndex);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetKillCount() const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    FWinLossRecord GetWinLossRecord() const;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetLevelIndex() const;

private:
    // 현재 게임 상태 저장 변수
    EGameState CurrentGameState;
};
