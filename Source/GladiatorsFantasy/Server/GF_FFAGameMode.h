#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GF_FFAGameMode.generated.h"

class AGFPlayerController;
class AGF_FFAPlayerState;
class AGF_FFAGameState;
class AGFAIController;
class AAIController;

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Spawning")
	FTransform GetAvailablePlayerStartTransform();

protected:
    // 현재 사용된 PlayerStart 목록
    UPROPERTY()
    TArray<AActor*> UsedPlayerStarts;
	
};
