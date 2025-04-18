#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFMainLobyWidget.generated.h"

class ACineCameraActor;
class ALevelSequenceActor;
class ULevelSequencePlayer;
class ULevelSequence;
class UButton;

UCLASS()
class GLADIATORSFANTASY_API UGFMainLobyWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CreditsBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitBtn;
	
	UFUNCTION()
	void PressedStartBtn();
	UFUNCTION()
	void PressedSettingBtn();
	UFUNCTION()
	void PressedCreditsBtn();
	UFUNCTION()
	void PressedExitBtn();
};
