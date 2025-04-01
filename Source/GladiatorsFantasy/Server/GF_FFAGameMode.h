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
    AGF_FFAGameMode();
    
    // 스폰 관련 함수
    UFUNCTION()
    void SpawnPlayer(AController* Controller);
    UFUNCTION()
    void SpawnAI();


    void NotifyPlayerKilled(AController* Killer);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
    TSubclassOf<AAIController> AIControllerClass;
    UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
    int32 MaxPlayers = 6;
    UPROPERTY(EditDefaultsOnly, Category = "Game Rules")
    int32 MatchDuration = 300;

    FTimerHandle MatchTimerHandle;
    FTimerHandle BotSpawnDelayHandle;
    


    virtual void BeginPlay() override;
    virtual void PostLogin(APlayerController* NewPlayer) override;
    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
    

private:
    void FillWithBotsIfNeeded();
    void StartMatchTimer();
    void EndMatch();
};
