#include "Props/SelectActor/SelectActor.h"

ASelectActor::ASelectActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshCompo->SetupAttachment(RootComponent);
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
	
}

void ASelectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

