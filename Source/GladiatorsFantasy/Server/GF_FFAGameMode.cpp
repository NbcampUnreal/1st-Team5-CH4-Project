#include "Server/GF_FFAGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Character/GFPlayerController.h"
#include "Server/GF_FFAGameState.h"
#include "Server/GF_FFAPlayerState.h"



FTransform AGF_FFAGameMode::GetAvailablePlayerStartTransform_Implementation()
{
    TArray<AActor*> AllStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllStarts);

    // 로그: 총 PlayerStart 수
    UE_LOG(LogTemp, Warning, TEXT("[PlayerStart] Total available in level: %d"), AllStarts.Num());

    TArray<AActor*> AvailableStarts;
    for (AActor* Start : AllStarts)
    {
        if (!UsedPlayerStarts.Contains(Start))
        {
            AvailableStarts.Add(Start);
        }
    }

    // 로그: 아직 사용 안 된 PlayerStart 수
    UE_LOG(LogTemp, Warning, TEXT("[PlayerStart] Unused: %d, Used: %d"), AvailableStarts.Num(), UsedPlayerStarts.Num());

    if (AvailableStarts.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("[PlayerStart] No available PlayerStart left!"));
        return FTransform(); // fallback
    }

    int32 Index = FMath::RandRange(0, AvailableStarts.Num() - 1);
    AActor* ChosenStart = AvailableStarts[Index];

    if (!ChosenStart)
    {
        UE_LOG(LogTemp, Error, TEXT("[PlayerStart] ChosenStart is null!"));
        return FTransform(); // fallback
    }

    UsedPlayerStarts.Add(ChosenStart);

    FVector Location = ChosenStart->GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("[PlayerStart] UsedCount: %d | Chosen: %s"),
        UsedPlayerStarts.Num(), *ChosenStart->GetName());

    return ChosenStart->GetActorTransform();
}

FTransform AGF_FFAGameMode::GetRandomPlayerStartTransform_Implementation() const
{
    TArray<AActor*> AllStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllStarts);

    if (AllStarts.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("[PlayerStart] No PlayerStart found in level!"));
        return FTransform();
    }

    int32 Index = FMath::RandRange(0, AllStarts.Num() - 1);
    AActor* ChosenStart = AllStarts[Index];

    if (!ChosenStart)
    {
        UE_LOG(LogTemp, Error, TEXT("[PlayerStart] Chosen PlayerStart is null!"));
        return FTransform();
    }

    UE_LOG(LogTemp, Warning, TEXT("[PlayerStart] Chosen: %s"), *ChosenStart->GetName());
    return ChosenStart->GetActorTransform();
}

FString AGF_FFAGameMode::GetTargetMapName() const
{
    return TEXT("TestLevelWS3");
}

// 테스트용
void AGF_FFAGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    AGF_FFAPlayerState::TestPlayerIndex = 1;
}
