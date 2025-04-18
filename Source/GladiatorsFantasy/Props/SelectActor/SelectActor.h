#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectActor.generated.h"

class UPostProcessComponent;

UENUM(Blueprintable)
enum class ESelectActor_Type :uint8
{
	SwordAndShield UMETA(DisplayName = "Sword"),
	Staff UMETA(DisplayName = "Staff"),
	Bow UMETA(DisplayName = "Bow"),
	DoubleHandedSword UMETA(DisplayName = "DoubleHandedSword"),
	MagicBook UMETA(DisplayName = "MagicBook"),
	Knight UMETA(DisplayName = "Knight"),
	Wizard UMETA(DisplayName = "Wizard"),
	Berserker UMETA(DisplayName = "Berserker"),
	Archer UMETA(DisplayName = "Archer"),
	End,
};

UCLASS()
class GLADIATORSFANTASY_API ASelectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASelectActor();

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="SelectActor")
	ESelectActor_Type Select_Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* SkeletalMeshCompo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	TObjectPtr<UPostProcessComponent> OutlineCompo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UAnimMontage* SelectAnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UAnimSequence* IdleAnimation;
	
	FString GetSelectType();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void ToggleOverlayMaterial(bool bEnable);

	void PlayAnimMontageSelect() { SkeletalMeshCompo->PlayAnimation(SelectAnimationMontage, false); bIsPlaySelectAnimation = true; }
	void PlayAnimIdle() { SkeletalMeshCompo->PlayAnimation(IdleAnimation,true); bIsPlaySelectAnimation = false; }

private:
	bool bIsPlaySelectAnimation;
};
