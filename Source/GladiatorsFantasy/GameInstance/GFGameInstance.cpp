
#include "GFGameInstance.h"
#include "Engine/Engine.h"
#include "Server/GF_FFAPlayerState.h"
#include "Server/GFBasePlayerState.h"

void UGFGameInstance::Init()
{
    Super::Init();

    // 초기 상태 및 통계값 초기화
    CurrentGameState = EGameState::EGS_MainMenu;
    LevelIndex = 0;

    // 실험용 더미 데이터 삽입
    FPlayerData Dummy;
    Dummy.PlayerCustomName = TEXT("TestPlayer");
    Dummy.Money = 999;
    Dummy.WinPoint = 1;
    Dummy.LossCount = 0;

    PlayerDataMap.Add(TEXT("DummyKey"), Dummy);
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

void UGFGameInstance::UpdatePlayerKillCounts(const TArray<AGF_FFAPlayerState*>& PlayerStates)
{
    // 기존 데이터를 비움
    PlayerKillCounts.Empty();

    // 각 플레이어 상태에서 킬 수를 가져와서, 플레이어 이름과 함께 저장합니다.
    for (AGF_FFAPlayerState* PS : PlayerStates)
    {
        if (PS)
        {
            // APlayerState의 기본 함수인 GetPlayerName()을 사용할 수 있습니다.
            FString PlayerId = PS->GetPlayerUniqueId();
            int32 Kills = PS->GetKillCount();
            PlayerKillCounts.Add(PlayerId, Kills);
        }
    }

    // 디버그 메시지
    if (GEngine)
    {
        for (auto& Elem : PlayerKillCounts)
        {
            FString DebugMsg = FString::Printf(TEXT("Player: %s, Kills: %d"), *Elem.Key, Elem.Value);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, DebugMsg);
        }
    }
}

int32 UGFGameInstance::GetTotalKillCount() const
{
    int32 TotalKills = 0;
    for (const auto& Elem : PlayerKillCounts)
    {
        TotalKills += Elem.Value;
    }
    return TotalKills;
}

void UGFGameInstance::AddWin(const FString& PlayerId)
{
    if (PlayerDataMap.Contains(PlayerId))
    {
        PlayerDataMap[PlayerId].WinPoint++;
        if (GEngine)
        {
            FString DebugMessage = FString::Printf(TEXT("%s Win count %d"), *PlayerId, PlayerDataMap[PlayerId].WinPoint);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, DebugMessage);
        }
    }
}

void UGFGameInstance::AddLoss(const FString& PlayerId)
{
    if (PlayerDataMap.Contains(PlayerId))
    {
        PlayerDataMap[PlayerId].LossCount++;
        if (GEngine)
        {
            FString DebugMessage = FString::Printf(TEXT("%s Loss count: %d"), *PlayerId, PlayerDataMap[PlayerId].LossCount);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
        }
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

int32 UGFGameInstance::GetLevelIndex() const
{
    return LevelIndex;
}

void UGFGameInstance::SetTopKillers(const TArray<AGF_FFAPlayerState*>& InTopKillers)
{
    TopKillers = InTopKillers;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Top Killers saved to GameInstance."));
    }
}

TArray<AGF_FFAPlayerState*> UGFGameInstance::GetTopKillersFromInstance() const
{
    return TopKillers;
}