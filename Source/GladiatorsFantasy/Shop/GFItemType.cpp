
#include "Shop/GFItemType.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

AGFItemType::AGFItemType()
{
	PrimaryActorTick.bCanEverTick = true;

    SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
    RootComponent = SpawnBox;

    SpawnRotation = FRotator::ZeroRotator;
}

void AGFItemType::BeginPlay()
{
	Super::BeginPlay();

	SpawnRandomItem();

    // 10초마다 CheckAndSpawn() 함수 호출
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGFItemType::CheckAndSpawn, 10.0f, true);
    }
	
}

void AGFItemType::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGFItemType::SpawnRandomItem()
{
    if (!SpawnBox)
    {
        UE_LOG(LogTemp, Error, TEXT("SpawnBox is not valid."));
        return;
    }

    FVector BoxCenter = SpawnBox->GetComponentLocation();
    FVector BoxExtent = SpawnBox->GetScaledBoxExtent();

    float RandX = FMath::RandRange(-BoxExtent.X, BoxExtent.X);
    float RandY = FMath::RandRange(-BoxExtent.Y, BoxExtent.Y);
    float RandZ = FMath::RandRange(-BoxExtent.Z, BoxExtent.Z);
    FVector RandomOffset(RandX, RandY, RandZ);

    FVector FinalSpawnLocation = BoxCenter + RandomOffset;

    // 0 또는 2을 랜덤하게 선택 (0: Apple, 1: Banana, 2: Chicken)
    int32 RandomIndex = FMath::RandRange(0, 2);
    TSubclassOf<AActor> ItemToSpawn = nullptr;
    if (RandomIndex == 0)
    {
        ItemToSpawn = AppleItemClass;
    }
    else if (RandomIndex == 1)
    {
        ItemToSpawn = BananaItemClass;
    }
    else if (RandomIndex == 2)
    {
        ItemToSpawn = ChickenItemClass;
    }

    if (ItemToSpawn && GetWorld())
    {
        FActorSpawnParameters SpawnParams;
        AActor* SpawnedItem = GetWorld()->SpawnActor<AActor>(ItemToSpawn, FinalSpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedItem)
        {
            UE_LOG(LogTemp, Log, TEXT("Spawned item at location: %s"), *FinalSpawnLocation.ToString());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn item."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemToSpawn is null or GetWorld() failed."));
    }
}

void AGFItemType::CheckAndSpawn()
{
    // SpawnBox의 영역에 겹치는 액터가 있는지 체크
    TArray<AActor*> OverlappingActors;
    SpawnBox->GetOverlappingActors(OverlappingActors);

    // 아이템이 없으면 스폰을 실행
    if (OverlappingActors.Num() == 0)
    {
        UE_LOG(LogTemp, Log, TEXT("No item detected in the spawner. Spawning a new one..."));
        SpawnRandomItem();
    }
}