
#include "Shop/GFBanana.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AGFBanana::AGFBanana()
{
	PrimaryActorTick.bCanEverTick = false;

	// 바나나 메시 컴포넌트를 생성하고 RootComponent로 지정
	BananaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BananaMesh"));
	RootComponent = BananaMesh;

	// Collision 설정: Query와 Physics 모드 모두 활성화하여 Hit 이벤트를 받을 수 있도록 함
	BananaMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BananaMesh->SetCollisionObjectType(ECC_WorldDynamic);
	BananaMesh->SetCollisionResponseToAllChannels(ECR_Block);

	// 물리적 충돌이 발생할 때 Hit 이벤트가 호출되도록 설정
	BananaMesh->SetNotifyRigidBodyCollision(true);

	// Hit 이벤트 델리게이트에 OnHit 함수를 바인딩
	BananaMesh->OnComponentHit.AddDynamic(this, &AGFBanana::OnHit);

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
	// 충돌한 대상이 캐릭터라면
	if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
	{
		FVector ImpulseDirection = GetActorForwardVector();

		// 캐릭터에 LaunchCharacter 함수를 통해 임펄스를 적용하여 슬립 효과 구현
		HitCharacter->LaunchCharacter(ImpulseDirection * SlipImpulseMagnitude, true, true);

		UE_LOG(LogTemp, Log, TEXT("Banana slip effect applied with impulse magnitude: %f"), SlipImpulseMagnitude);

		// 효과 적용 후 바나나 아이템 제거
		Destroy();
	}
}

