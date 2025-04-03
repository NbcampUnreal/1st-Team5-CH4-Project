#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GF_FFAMatchResultWidget.generated.h"

class UTextBlock;

UCLASS()
class GLADIATORSFANTASY_API UGF_FFAMatchResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ShowMatchResult(class APlayerState* Winner);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MatchResultText;
};
