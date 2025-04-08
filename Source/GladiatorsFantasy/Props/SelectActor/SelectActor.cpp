#include "Props/SelectActor/SelectActor.h"

#include "Components/PostProcessComponent.h"

ASelectActor::ASelectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshCompo->SetupAttachment(RootComponent);
	SkeletalMeshCompo->SetRenderCustomDepth(false);
	
	OutlineCompo = CreateDefaultSubobject<UPostProcessComponent>(TEXT("OutlineCompo"));
	OutlineCompo->SetupAttachment(SkeletalMeshCompo);
	OutlineCompo->bEnabled = false;
}

FString ASelectActor::GetSelectType()
{
	switch (Select_Type)
	{
		case ESelectActor_Type::SwordAndShield:
			return "SwordAndShieldCharacter";
		case ESelectActor_Type::Staff:
			return "StaffCharacter";
		case ESelectActor_Type::Bow:
			return "BowCharacter";
		case ESelectActor_Type::DoubleHandedSword:
			return "DoubleHandedCharacter";
		case ESelectActor_Type::MagicBook:
			return "MagicBookCharacter";
		case ESelectActor_Type::Knight:
			return "Knight";
		case ESelectActor_Type::Berserker:
			return "Berserker";
		case ESelectActor_Type::Archer:
			return "Archer";
		case ESelectActor_Type::Wizard:
			return "Wizard";
		default:
			return "Error";
	}
}

void ASelectActor::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshCompo->SetRenderCustomDepth(false);
}

void ASelectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASelectActor::ToggleOverlayMaterial(bool bEnable)
{
	if (!SkeletalMeshCompo)
	{
		UE_LOG(LogTemp, Warning, TEXT("ToggleOverlayMaterial: Mesh가 유효하지 않습니다."));
		return;
	}
	SkeletalMeshCompo->SetRenderCustomDepth(bEnable);
	
	// if (bEnable)
	// {
	// 	UMaterialInterface* OverlayMat = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/SH/Material/MT_OutLine.MT_OutLine"));
	// 	if (OverlayMat)
	// 	{
	// 		SkeletalMeshCompo->SetOverlayMaterial(OverlayMat);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("ToggleOverlayMaterial: Overlay 머티리얼 로드 실패"));
	// 	}
	// }
	// else
	// {
	// 	SkeletalMeshCompo->SetOverlayMaterial(nullptr);
	// }
}