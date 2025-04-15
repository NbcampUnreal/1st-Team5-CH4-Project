#include "Props/TDMGame/GFDeadZoneActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AGFDeadZoneActor::AGFDeadZoneActor()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("TRiggerZone"));
	RootComponent = TriggerZone;

	// 충돌 설정에서 Pawn만 오버랩
	TriggerZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerZone->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerZone->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AGFDeadZoneActor::OnOverlapBegin);
}


void AGFDeadZoneActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AGFDeadZoneActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->GetClass()->ImplementsInterface(
		StaticLoadClass(UInterface::StaticClass(), nullptr, TEXT("/Game/BMMCSystem/Blueprints/Interfaces/BPI_Components_Combat.BPI_Components_Combat_C"))))
	{
		UFunction* Func = OtherActor->FindFunction(FName("I_DirectDeath"));
		if (Func)
		{
 			OtherActor->ProcessEvent(Func, nullptr);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[DeadZone] I_DirectDeath NOT FOUND on %s"), *OtherActor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[DeadZone] BPI_Components_Combat NOT FOUND on %s"), *OtherActor->GetName());
	}
}



