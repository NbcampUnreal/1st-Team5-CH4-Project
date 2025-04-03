#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GF_FFAPlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddKill();
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetKillCount() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 KillCount = 0;
};
