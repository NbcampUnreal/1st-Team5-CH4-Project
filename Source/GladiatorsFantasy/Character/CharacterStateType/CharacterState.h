#pragma once
#include "CoreMinimal.h"
#include "CharacterState.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAnimationData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Velocity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Velocity2D;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector WorldLocation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FRotator WorldRotation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Acceleration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Acceleration2D;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float VelocityAngle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float AccelerationAngle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float PivotAngle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float GroundSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsAcceleration;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool ShouldMove;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsFalling;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsFlying;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsCrouch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsJump;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsCouch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float VelocityZ;
};