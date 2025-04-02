#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GF_FFAGameState.generated.h"

class AGF_FFAPlayerState;

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game|FFA")
	TArray<AGF_FFAPlayerState*> GetTopKillers() const;
};
