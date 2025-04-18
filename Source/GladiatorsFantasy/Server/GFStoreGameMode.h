#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "UnrealInterface/GFMatchEndInterface.h"
#include "GFStoreGameMode.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFStoreGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AGFStoreGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Character")
	TSubclassOf<class AGFShopCharacterActor> ShopCharacterClass;
	
	UPROPERTY(EditAnywhere, Category = "Character Data")
	UDataTable* StoreCharacterDataTable;


	UFUNCTION(BlueprintCallable, Category = "Shop")
	void CheckAllPlayersReady();

	// 스폰 위치 반환 함수
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetOrderedPlayerStartPoints();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	// 플레이어 배치하는 함수
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
	// 액터 배치하는 함수
	void SpawnShopCharacterRelativeTo(AController* PC, AActor* StartSpot);

	void TravelToNextLevel();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Level Travel")
	TArray<FString> LevelPaths;

	bool IsStartSpotAvailable(AActor* StartSpot) const;
	TSet<AActor*> UsedStartSpots; // 이미 사용한 StartSpot 저장



};
