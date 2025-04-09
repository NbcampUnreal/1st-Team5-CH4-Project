#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA(DisplayName = "Run"),
	Sprint UMETA(DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class EStance : uint8
{
	Stand UMETA(DisplayName = "Stand"),
	Crouch UMETA(DisplayName = "Crouch")
};
