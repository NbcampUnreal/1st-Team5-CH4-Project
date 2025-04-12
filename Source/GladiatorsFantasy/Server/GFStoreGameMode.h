#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GFStoreGameMode.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFStoreGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGFStoreGameMode();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UGFShop> StoreWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	void CheckAllPlayersReady();

	// 스폰 위치 반환 함수
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetOrderedPlayerStartPoints();
	
	virtual void BeginPlay() override;
	// 플레이어 배치하는 함수
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;

	void TravelToNextLevel();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Level Travel")
	TArray<FString> LevelPaths;

};
