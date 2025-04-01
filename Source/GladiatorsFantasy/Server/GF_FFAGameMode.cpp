#include "Server/GF_FFAGameMode.h"
#include "GF_FFAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Character/GFPlayerController.h"
#include "Server/GF_FFAGameState.h"
#include "Server/GF_FFAPlayerState.h"
#include "AI/GFAIController.h"

AGF_FFAGameMode::AGF_FFAGameMode()
{
    PlayerControllerClass = AGFPlayerController::StaticClass();
    PlayerStateClass = AGF_FFAPlayerState::StaticClass();
    GameStateClass = AGF_FFAGameState::StaticClass();
    AIControllerClass = AGFAIController::StaticClass();
    
    bUseSeamlessTravel = true;
}

void AGF_FFAGameMode::NotifyPlayerKilled(AController* Killer)
{
    if (Killer && Killer->PlayerState)
    {
        if (AGF_FFAPlayerState* PS = Cast<AGF_FFAPlayerState>(Killer->PlayerState))
        {
            PS->AddKill();
        }
    }
}




void AGF_FFAGameMode::SpawnPlayer(AController* Controller)
{
    if (!Controller) return;

    AActor* StartSpot = ChoosePlayerStart(Controller);
    if (!StartSpot) return;

    RestartPlayerAtPlayerStart(Controller, StartSpot);
}

void AGF_FFAGameMode::SpawnAI()
{
    if (!AIControllerClass) return;

    AActor* StartSpot = ChoosePlayerStart(nullptr);
    if (!StartSpot) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // AIController 스폰
    AAIController* AIController = GetWorld()->SpawnActor<AAIController>(
        AIControllerClass,
        StartSpot->GetActorLocation(),
        StartSpot->GetActorRotation(),
        SpawnParams
    );

    if (AIController)
    {
        // 플레이어처럼 시작
        RestartPlayerAtPlayerStart(AIController, StartSpot);
    }
}

void AGF_FFAGameMode::BeginPlay()
{
    Super::BeginPlay();

    /*GetWorldTimerManager().SetTimer(
        BotSpawnDelayHandle,
        this,
        &AGF_FFAGameMode::FillWithBotsIfNeeded,
        3.0f,
        false
    );*/

    
    if (AGF_FFAGameState* GS = GetGameState<AGF_FFAGameState>())
    {
        GS->StartCountdown(MatchDuration);
    }

    StartMatchTimer();
}

void AGF_FFAGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // 나중에는 Expected를 GameInstance에서 받아와야 함
    /*UGFGameInstance* GI = Cast<UGFGameInstance>(GetGameInstance());
    if (!GI) return;*/

    int32 TotalPlayers = GetNumPlayers();
//    int32 Expected = GI->ExpectedHumanPlayers;
    int32 Expected = 4;

    UE_LOG(LogTemp, Warning, TEXT("PostLogin: %d / Expected: %d"), TotalPlayers, Expected);

    if (TotalPlayers == Expected)
    {
        FillWithBotsIfNeeded();
    }

    SpawnPlayer(NewPlayer);
}

AActor* AGF_FFAGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    TArray<AActor*> StartPoints;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), StartPoints);

    // 이미 사용된 스폰 포인트 추적을 위한 set
    static TSet<AActor*> UsedStartPoints;

    // 사용되지 않은 것만 필터링
    TArray<AActor*> Available;
    for (AActor* Start : StartPoints)
    {
        if (!UsedStartPoints.Contains(Start))
        {
            Available.Add(Start);
        }
    }

    if (Available.Num() > 0)
    {
        int32 Index = FMath::RandRange(0, Available.Num() - 1);
        AActor* Chosen = Available[Index];
        UsedStartPoints.Add(Chosen);
        return Chosen;
    }

    // fallback
    return Super::ChoosePlayerStart_Implementation(Player);
}


void AGF_FFAGameMode::FillWithBotsIfNeeded()
{
    int32 CurrentPlayers = GetNumPlayers();
    int32 BotsToSpawn = MaxPlayers - CurrentPlayers;

    UE_LOG(LogTemp, Log, TEXT("CurrentPlayer: %d, BotsToSpawn: %d"), CurrentPlayers, BotsToSpawn);

    for (int32 i = 0; i < BotsToSpawn; i++)
    {
        SpawnAI();
    }
}

void AGF_FFAGameMode::StartMatchTimer()
{
    GetWorldTimerManager().SetTimer(
        MatchTimerHandle,
        this,
        &AGF_FFAGameMode::EndMatch,
        MatchDuration,
        false
    );
}

void AGF_FFAGameMode::EndMatch()
{
    APlayerState* TopPlayer = nullptr;
    int32 HighestKills = -1;

    // 최다 킬 수 플레이어 선정
    for (APlayerState* PS : GameState->PlayerArray)
    {
        AGF_FFAPlayerState* FFA_PS = Cast<AGF_FFAPlayerState>(PS);
        if (FFA_PS && FFA_PS->GetKillCount() > HighestKills)
        {
            HighestKills = FFA_PS->GetKillCount();
            TopPlayer = FFA_PS;
        }
    }

    if (AGF_FFAPlayerState* Winner = Cast<AGF_FFAPlayerState>(TopPlayer))
    {
        Winner->AddVictoryPoint();
        UE_LOG(LogTemp, Log, TEXT("Winner is %s with %d kills"), *Winner->GetPlayerName(), Winner->GetKillCount());
    }
}
