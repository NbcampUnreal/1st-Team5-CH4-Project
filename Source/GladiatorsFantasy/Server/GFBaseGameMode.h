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
	AGFBaseGameMode();

	// 스폰 관련 변수들============
	UPROPERTY(BlueprintReadOnly)
	bool bAllPlayersReady;


	UFUNCTION(BlueprintCallable)
	virtual FString GetTargetMapName() const;

	UFUNCTION(BlueprintCallable)
	void TravelToAssignedLevel();

	UFUNCTION(BlueprintCallable)
	void TravelToStoreLevel();
	UFUNCTION(BlueprintCallable)
	void TarvelToLastLevel() const;


	UFUNCTION(BlueprintCallable)
	FString GetServerAddress();

	// 스폰 관련 함수들============
	UFUNCTION(BlueprintCallable)
	bool AreAllPlayersReady();


	void ChangeLevel();
};
