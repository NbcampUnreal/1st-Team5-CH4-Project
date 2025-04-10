
#include "Shop/GFApple.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/GFBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

AGFApple::AGFApple()
{
	PrimaryActorTick.bCanEverTick = false;

    // 메시 컴포넌트 초기화 및 루트 컴포넌트 지정
    AppleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AppleMesh"));
    RootComponent = AppleMesh;

    // 충돌 설정
    AppleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    AppleMesh->SetCollisionObjectType(ECC_WorldDynamic);

    // 모든 채널에 대해 Block 처리하도록 기본 설정
    AppleMesh->SetCollisionResponseToAllChannels(ECR_Block);

    // Hit 이벤트를 받기 위한 설정
    AppleMesh->SetGenerateOverlapEvents(true);

    // Hit 이벤트 델리게이트 바인딩
    AppleMesh->OnComponentHit.AddDynamic(this, &AGFApple::OnHit);

    AppleMesh->OnComponentBeginOverlap.AddDynamic(this, &AGFApple::OnOverlapBegin);

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
    if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
    {
        // 스턴을 적용하기 위한 캐릭터 클래스인지 캐스팅
        if (AGFBaseCharacter* PlayerCharacter = Cast<AGFBaseCharacter>(HitCharacter))
        {
            PlayerCharacter->ApplyStun(StunDuration);
        }

        //아이템 제거
        Destroy();
    }
}

void AGFApple::OnOverlapBegin(
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

//캐릭터 손 부착
void AGFApple::PickUp(ACharacter* NewOwner)
{
    if (NewOwner)
    {
        // 물리 시뮬레이션 및 충돌 끄기
        AppleMesh->SetSimulatePhysics(false);
        AppleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        // 캐릭터의 메쉬 소켓에 부착
        AttachToComponent(NewOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("HandSwordSocket"));
    }
}

void AGFApple::Throw(FVector ThrowImpulse)
{
    // 부착 해제
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    // 충돌 및 물리 시뮬레이션 복구
    AppleMesh->SetSimulatePhysics(true);
    AppleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // 지정한 임펄스만큼 힘을 가해 던짐
    AppleMesh->AddImpulse(ThrowImpulse, NAME_None, true);
}

