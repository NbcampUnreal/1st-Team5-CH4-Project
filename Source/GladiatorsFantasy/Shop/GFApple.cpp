
#include "Shop/GFApple.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Character/GFBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

AGFApple::AGFApple()
{
	PrimaryActorTick.bCanEverTick = false;

    // 메시 컴포넌트 초기화 및 루트 컴포넌트 지정
    AppleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMesh"));
    RootComponent = AppleMesh;

    // 충돌 설정: Query와 Physics 둘 다 활성화하여 Hit 이벤트를 받을 수 있도록 설정
    AppleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AppleMesh->SetCollisionObjectType(ECC_WorldDynamic);

    // 모든 채널에 대해 Block 처리하도록 기본 설정 (프로젝트에 따라 조정 필요)
    AppleMesh->SetCollisionResponseToAllChannels(ECR_Block);

    // Hit 이벤트를 받기 위한 설정
    AppleMesh->SetNotifyRigidBodyCollision(true);

    // Hit 이벤트 델리게이트 바인딩
    AppleMesh->OnComponentHit.AddDynamic(this, &AGFApple::OnHit);

    StunDuration = 2.0f;  // 기본 스턴 지속 시간
}

void AGFApple::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGFApple::OnHit(
    UPrimitiveComponent* HitComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit
)
{
    // 충돌한 대상이 ACharacter인지 확인
    if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
    {
        // 스턴을 적용하기 위한 캐릭터 클래스인지 캐스팅 (프로젝트에 맞게 적용)
        if (AGFBaseCharacter* PlayerCharacter = Cast<AGFBaseCharacter>(HitCharacter))
        {
        }

        // 한 번의 충돌 후 아이템 제거 (필요에 따라 비활성화 등 다른 처리를 할 수 있음)
        Destroy();
    }
}

