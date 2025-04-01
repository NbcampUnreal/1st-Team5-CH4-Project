
#include "GFGameInstance.h"
#include "Engine/Engine.h"

void UGFGameInstance::Init()
{
    Super::Init();

    // 초기 상태 및 통계값 초기화
    CurrentGameState = EGameState::EGS_MainMenu;
    KillCount = 0;
    LevelIndex = 0;
    WinLossRecord.WinCount = 0;
    WinLossRecord.LossCount = 0;
}

void UGFGameInstance::SetGameState(EGameState NewState)
{
    CurrentGameState = NewState;
    FString StateName;
    switch (CurrentGameState)
    {
    case EGameState::EGS_MainMenu:
        StateName = "Main Menu";
        break;
    case EGameState::EGS_InGame:
        StateName = "In Game";
        break;
    case EGameState::EGS_GameOver:
        StateName = "Game Over";
        break;
    default:
        StateName = "Unknown";
        break;
    }

    // 디버그 메시지
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("Game state changed to: %s"), *StateName);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, DebugMessage);
    }
}

EGameState UGFGameInstance::GetGameState() const
{
    return CurrentGameState;
}

void UGFGameInstance::AddKillCount(int32 Kills)
{
    KillCount += Kills;
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("Kill count increased by %d. Total kills: %d"), Kills, KillCount);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugMessage);
    }
}

void UGFGameInstance::AddWin()
{
    WinLossRecord.WinCount++;
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("Win count increased. Total wins: %d"), WinLossRecord.WinCount);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, DebugMessage);
    }
}

void UGFGameInstance::AddLoss()
{
    WinLossRecord.LossCount++;
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("Loss count increased. Total losses: %d"), WinLossRecord.LossCount);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
    }
}

void UGFGameInstance::SetLevelIndex(int32 NewLevelIndex)
{
    LevelIndex = NewLevelIndex;
    if (GEngine)
    {
        FString DebugMessage = FString::Printf(TEXT("Level index set to: %d"), LevelIndex);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
    }
}

int32 UGFGameInstance::GetKillCount() const
{
    return KillCount;
}

FWinLossRecord UGFGameInstance::GetWinLossRecord() const
{
    return WinLossRecord;
}

int32 UGFGameInstance::GetLevelIndex() const
{
    return LevelIndex;
}