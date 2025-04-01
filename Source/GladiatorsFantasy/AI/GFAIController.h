#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GFAIController.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORSFANTASY_API AGFAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void OnAIDeath();

protected:
	void RequestRespawn();

	FTimerHandle RespawnTimerHandle;
};
