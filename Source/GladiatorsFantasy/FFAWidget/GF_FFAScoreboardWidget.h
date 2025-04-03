#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GF_FFAScoreboardWidget.generated.h"

class UTextBlock;

UCLASS()
class GLADIATORSFANTASY_API UGF_FFAScoreboardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateTimer(int32 TimerRemainingSeconds);
	UFUNCTION(BlueprintCallable)
	void UpdateKillCount(int32 KillCount);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerText;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillCountText;
};
