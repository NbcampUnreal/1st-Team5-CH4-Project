#include "Server/GFStoreGameMode.h"
#include "Server/GFStorePlayerController.h"
#include "Server/GFStorePlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/GFGameInstance.h"
#include "Character/Store/GFShopCharacterActor.h"
#include "DataTable/StoreSpawn/FGFStoreCharacterSpawnRow.h"


AGFStoreGameMode::AGFStoreGameMode()
{
    LevelPaths = {
        TEXT("/Game/WS/TestLevel2?listen"),
        TEXT("/Game/WS/TestLevelWS3?listen"),
        TEXT("/Game/SH/BattletLevel4?listen")
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

void AGFStoreGameMode::PostLogin(APlayerController* NewPlayer)
{
    if (!NewPlayer || !HasAuthority()) return;

    AGFBasePlayerState* PS = NewPlayer->GetPlayerState<AGFBasePlayerState>();
    if (PS)
    {
        PS->LoadFromGameInstance();

        //// 테스트용 캐릭터 리스트 (정적 캐시)
        //static const TArray<FString> TestCharacterNames = {
        //    TEXT("Knight"), TEXT("Berserker"), TEXT("Archer"),
        //    TEXT("Wizard"), TEXT("Knight"), TEXT("Berserker")
        //};

        //static int32 PlayerIndex = 0;

        //const int32 NameCount = TestCharacterNames.Num();
        //const int32 AssignedIndex = PlayerIndex % NameCount;

        //if (TestCharacterNames.IsValidIndex(AssignedIndex))
        //{
        //    PS->SetCharacterBPName(TestCharacterNames[AssignedIndex]);
        //    UE_LOG(LogTemp, Log, TEXT("Assigned test character %s to Player %d"),
        //        *TestCharacterNames[AssignedIndex], AssignedIndex);
        //}

        ///*AActor* StartSpot = ChoosePlayerStart(NewPlayer);
        //SpawnShopCharacterRelativeTo(NewPlayer, StartSpot);*/

        //PlayerIndex++;
    }

    Super::PostLogin(NewPlayer);

    
}

AActor* AGFStoreGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

    for (AActor* Start : PlayerStarts)
    {
        if (!UsedStartSpots.Contains(Start) && IsStartSpotAvailable(Start))
        {
            UsedStartSpots.Add(Start); // 사용된 것으로 기록
            return Start;
        }
    }

    // 전부 사용 중이면 기본 처리
    return Super::ChoosePlayerStart_Implementation(Player);
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

        NewPawn->SetActorRotation(SpawnRotation);
        NewPlayer->SetControlRotation(SpawnRotation);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn pawn for player."));
    }
    SpawnShopCharacterRelativeTo(NewPlayer, StartSpot);
}

void AGFStoreGameMode::SpawnShopCharacterRelativeTo(AController* PC, AActor* StartSpot)
{
    if (!PC || !StartSpot || !ShopCharacterClass) return;

    AGFBasePlayerState* BPS = PC->GetPlayerState<AGFBasePlayerState>();

    if (!StoreCharacterDataTable || !HasAuthority()) return;

    const FName RowName = FName(*BPS->GetCharacterBPName());
    const FGFStoreCharacterSpawnData* Row = StoreCharacterDataTable->FindRow<FGFStoreCharacterSpawnData>(RowName, TEXT("ShopCharMeshLookup"));

    if (!Row) return;

    FVector Origin = StartSpot->GetActorLocation();
    FRotator Facing = StartSpot->GetActorRotation();

    // Offset -> 미리 측정한 상대 위치
    FVector Offset = Row->LocationOffset;
    
    FVector ShopLocation = Origin + Offset;

    FRotator ShopRotation = Facing;

    FActorSpawnParameters Params;
    Params.Owner = PC;

    AGFShopCharacterActor* ShopActor = GetWorld()->SpawnActor<AGFShopCharacterActor>(
        ShopCharacterClass,
        ShopLocation,
        ShopRotation,
        Params
    );

    if (AGFBasePlayerState* PS = PC->GetPlayerState<AGFBasePlayerState>())
    {
        ShopActor->SetupCharacterMesh(PS->GetCharacterBPName());
    }
    UE_LOG(LogTemp, Warning, TEXT("SHOP SPAWN >> PC: %s, Location: %s"),
        *GetNameSafe(PC),
        *StartSpot->GetActorLocation().ToString()); 
}

void AGFStoreGameMode::TravelToNextLevel()
{
    UGFGameInstance* GI = GetGameInstance<UGFGameInstance>();
    if (!GI) return;

    FString NextLevelPath = LevelPaths.IsValidIndex(GI->GetNextLevelIndex())
        ? LevelPaths[GI->GetNextLevelIndex()]
        : TEXT("/Game/Maps/FallbackLevel?listen");

    GI->IncrementLevelIndex();

    UE_LOG(LogTemp, Log, TEXT("Traveling to: %s"), *NextLevelPath);
    GetWorld()->ServerTravel(NextLevelPath);
}

bool AGFStoreGameMode::IsStartSpotAvailable(AActor* StartSpot) const
{
    FVector SpotLocation = StartSpot->GetActorLocation();
    float Radius = 100.0f;

    TArray<FOverlapResult> Overlaps;
    FCollisionQueryParams Params;
    Params.bTraceComplex = false;
    Params.bReturnPhysicalMaterial = false;

    bool bHasOverlap = GetWorld()->OverlapMultiByObjectType(
        Overlaps,
        SpotLocation,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECC_Pawn),
        FCollisionShape::MakeSphere(Radius),
        Params
    );

    return !bHasOverlap;
}

