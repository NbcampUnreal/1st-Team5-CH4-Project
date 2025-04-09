#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GFBaseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORSFANTASY_API AGFBaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	virtual FString GetTargetMapName() const;

	UFUNCTION(BlueprintCallable)
	void TravelToAssignedLevel();

	UFUNCTION(BlueprintCallable)
	void TravelToAssignedLevelForBP(const FString& InLevelName);


	UFUNCTION(BlueprintCallable)
	FString GetServerAddress();

	void ChangeLevel();
};
