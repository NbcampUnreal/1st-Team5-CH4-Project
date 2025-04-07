#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFLobyWidget.generated.h"

class UButton;

UCLASS()
class GLADIATORSFANTASY_API UGFLobyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackBtn;

	UFUNCTION()
	void PressedStartBtn();
	UFUNCTION()
	void PressedBackBtn();
};
