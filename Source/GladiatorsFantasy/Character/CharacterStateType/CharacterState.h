#pragma once
#include "CoreMinimal.h"
#include "CharacterState.generated.h"

USTRUCT(BlueprintType)
struct FPlayerAnimationData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Velocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Velocity2D = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector WorldLocation = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FRotator WorldRotation = FRotator::ZeroRotator;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Acceleration = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	FVector Acceleration2D = FVector::ZeroVector;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float VelocityAngle = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float AccelerationAngle = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float PivotAngle = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float GroundSpeed = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsAcceleration = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool ShouldMove = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsFalling = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsFlying = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsCrouch = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsJump = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	bool IsCouch = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "CharacterStateData")
	float VelocityZ = 0.0f;
};