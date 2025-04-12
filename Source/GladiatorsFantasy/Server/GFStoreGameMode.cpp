#include "Server/GFStoreGameMode.h"
#include "Server/GFStorePlayerController.h"
#include "Server/GFStorePlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/GFGameInstance.h"


AGFStoreGameMode::AGFStoreGameMode()
{
    LevelPaths = {
        TEXT("/Game/WS/TestLevel2?listen"),
        TEXT("/Game/WS/TestLevelWS3?listen")
    };
}

void AGFStoreGameMode::CheckAllPlayersReady()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC) continue;

        AGFStorePlayerState* PS = PC->GetPlayerState<AGFStorePlayerState>();
        if (!PS || !PS->bIsReady)
        {
            return; // 아직 준비 안된 사람 있음
        }
    }
    
    // 모두 준비 완료
    TravelToNextLevel();
}

TArray<AActor*> AGFStoreGameMode::GetOrderedPlayerStartPoints()
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    // 최대 6개까지만 사용
    if (PlayerStarts.Num() > 6)
    {
        PlayerStarts.SetNum(6);
    }

    return PlayerStarts;
}

void AGFStoreGameMode::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World) return;

   
    TArray<AActor*> StartPoints = GetOrderedPlayerStartPoints();
    if (StartPoints.Num() < 6)
    {
        UE_LOG(LogTemp, Error, TEXT("Not enough PlayerStart actors in level!"));
        return;
    }

    int32 PlayerIndex = 0;

    
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        if (PlayerIndex >= StartPoints.Num())
        {
            UE_LOG(LogTemp, Warning, TEXT("More players than PlayerStarts."));
            break;
        }

        APlayerController* PC = It->Get();
        if (!PC) continue;

        
        RestartPlayerAtPlayerStart(PC, StartPoints[PlayerIndex]);

        // GameInstance 데이터 불러오기
        AGFBasePlayerState* PS = PC->GetPlayerState<AGFBasePlayerState>();
        if (PS)
        {
            PS->LoadFromGameInstance();
        }

        AGFStorePlayerController* StorePC = Cast<AGFStorePlayerController>(PC);
        if (StorePC)
        {
            StorePC->ClientShowStoreUI();
        }

        PlayerIndex++;
    }
}

void AGFStoreGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
    if (!NewPlayer || !StartSpot)
    {
        UE_LOG(LogTemp, Warning, TEXT("RestartPlayerAtPlayerStart: Invalid player or start spot."));
        return;
    }

   
    if (APawn* ExistingPawn = NewPlayer->GetPawn())
    {
        ExistingPawn->Destroy();
    }

   
    TSubclassOf<APawn> PawnClass = GetDefaultPawnClassForController(NewPlayer);
    if (!PawnClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("RestartPlayerAtPlayerStart: No default pawn class."));
        return;
    }

   
    FVector SpawnLocation = StartSpot->GetActorLocation();
    FRotator SpawnRotation = StartSpot->GetActorRotation();

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = NewPlayer;
    SpawnParams.Instigator = GetInstigator();

    APawn* NewPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnLocation, SpawnRotation, SpawnParams);
    if (NewPawn)
    {
        NewPlayer->Possess(NewPawn);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn pawn for player."));
    }
}

void AGFStoreGameMode::TravelToNextLevel()
{
    UGFGameInstance* GI = GetGameInstance<UGFGameInstance>();
    if (!GI) return;

    FString NextLevelPath = LevelPaths.IsValidIndex(GI->GetNextLevelIndex())
        ? LevelPaths[GI->GetNextLevelIndex()]
        : TEXT("/Game/Maps/FallbackLevel");

    GI->IncrementLevelIndex();

    UE_LOG(LogTemp, Log, TEXT("Traveling to: %s"), *NextLevelPath);
    GetWorld()->ServerTravel(NextLevelPath);
}

