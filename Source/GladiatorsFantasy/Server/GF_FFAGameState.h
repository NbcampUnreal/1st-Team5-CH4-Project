#pragma once

#include "CoreMinimal.h"
#include "Server/GFBaseGameState.h"
#include "GF_FFAGameState.generated.h"

class AGF_FFAPlayerState;

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAGameState : public AGFBaseGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game|FFA")
	TArray<AGF_FFAPlayerState*> GetTopKillers() const;
};
