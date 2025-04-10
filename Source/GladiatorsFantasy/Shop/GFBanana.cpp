
#include "Shop/GFBanana.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/GFBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

AGFBanana::AGFBanana()
{
	PrimaryActorTick.bCanEverTick = false;

	// 바나나 메시 컴포넌트를 생성하고 RootComponent로 지정
	BananaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BananaMesh"));
	RootComponent = BananaMesh;

	// Collision 설정
	BananaMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BananaMesh->SetCollisionObjectType(ECC_WorldDynamic);
	BananaMesh->SetCollisionResponseToAllChannels(ECR_Block);

	// 물리적 충돌이 발생할 때 Hit 이벤트가 호출되도록 설정
	BananaMesh->SetGenerateOverlapEvents(true);

	// Hit 이벤트 델리게이트에 OnHit 함수를 바인딩
	BananaMesh->OnComponentHit.AddDynamic(this, &AGFBanana::OnHit);

	BananaMesh->OnComponentBeginOverlap.AddDynamic(this, &AGFBanana::OnOverlapBegin);

	// 기본 슬립값
	SlipImpulseMagnitude = 1000.0f;
}

void AGFBanana::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGFBanana::OnHit(
	UPrimitiveComponent* HitComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
	{
		FVector ImpulseDirection = GetActorForwardVector();

		HitCharacter->LaunchCharacter(ImpulseDirection * SlipImpulseMagnitude, true, true);

		UE_LOG(LogTemp, Log, TEXT("Banana slip effect applied with impulse magnitude: %f"), SlipImpulseMagnitude);

		//아이템 제거
		Destroy();
	}
}

void AGFBanana::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	// OtherActor가 캐릭터라면, 아이템을 픽업
	if (ACharacter* OverlappedCharacter = Cast<ACharacter>(OtherActor))
	{
		// 자동으로 PickUp 호출해서 캐릭터의 손(소켓)에 부착
		PickUp(OverlappedCharacter);
	}
}

void AGFBanana::PickUp(ACharacter* NewOwner)
{
	if (NewOwner)
	{
		// 물리 시뮬레이션 및 충돌 끄기
		BananaMesh->SetSimulatePhysics(false);
		BananaMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// 캐릭터의 메쉬 소켓에 부착"Hand_R"라는 소켓이 존재한다고 가정
		AttachToComponent(NewOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandSwordSocket"));
	}
}


void AGFBanana::Throw(FVector ThrowImpulse)
{
	// 부착 해제
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// 충돌 및 물리 시뮬레이션 복구
	BananaMesh->SetSimulatePhysics(true);
	BananaMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	BananaMesh->AddImpulse(ThrowImpulse, NAME_None, true);
}
