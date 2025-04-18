// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../CharacterStateType/CharacterState.h"
#include "../CharacterStateType/CharacterStateFlag.h"
#include "GFAnimInstanceBase.generated.h"

UCLASS()
class GLADIATORSFANTASY_API UGFAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
private:
	class AGFBaseCharacter* OwnerPlayer;
	class UCharacterMovementComponent* PlayerMovement;
	EMovementState PlayerMoveState;
	EStance PlayerStance;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "CurrentStateData")
	FPlayerAnimationData PlayerStateData;
protected:
	float CalculateDirection(const FVector& Velocity, const FRotator& BaseRotation) const;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
