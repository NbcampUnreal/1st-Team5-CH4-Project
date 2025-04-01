#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GF_FFAPlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AGF_FFAPlayerState();

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetKillCount() const;
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetVictoryPoints() const;

	void AddKill();
	void AddVictoryPoint();

protected:
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Score")
	int32 KillCount = 0;
	UPROPERTY(Replicated, VisibleAnywhere, Category = "Score")
	int32 VictoryPoints = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



};
