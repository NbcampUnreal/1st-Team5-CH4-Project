
#include "Shop/AGFChicken.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Character/GFBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

AAGFChicken::AAGFChicken()
{
	PrimaryActorTick.bCanEverTick = false;

	// 메시 컴포넌트 생성 및 루트 컴포넌트 지정
	ChickenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChickenMesh"));
	RootComponent = ChickenMesh;

	// 충돌 설정 (필요에 따라 조정)
	ChickenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ChickenMesh->SetCollisionObjectType(ECC_WorldDynamic);
	ChickenMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ChickenMesh->SetGenerateOverlapEvents(true);
	ChickenMesh->OnComponentBeginOverlap.AddDynamic(this, &AAGFChicken::OnOverlapBegin);

	bIsEquipped = false;
}

void AAGFChicken::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAGFChicken::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!bIsEquipped)
	{
		// OtherActor가 캐릭터라면, 아이템을 픽업
		if (ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor))
		{
			// 자동으로 PickUp 호출해서 캐릭터의 손(소켓)에 부착
			PickUp(OverlappedCharacter);
		}
	}
}

void AAGFChicken::PickUp(ACharacter* NewOwner)
{
	if (NewOwner)
	{
		ChickenMesh->SetSimulatePhysics(false);
		ChickenMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		AttachToComponent(NewOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandSocket"));
		bIsEquipped = true;
	}
}


void AAGFChicken::Throw(FVector ThrowImpulse)
{
	
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		ChickenMesh->SetSimulatePhysics(true);
		ChickenMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		ChickenMesh->AddImpulse(ThrowImpulse, NAME_None, true);

		if (ThrowSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ThrowSound, GetActorLocation());
		}
	bIsEquipped = false;
}

