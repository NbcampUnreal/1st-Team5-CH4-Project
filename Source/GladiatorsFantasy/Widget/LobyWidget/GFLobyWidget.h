#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFLobyWidget.generated.h"

class UTextBlock;
class UGFChatWidget;
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
	TObjectPtr<UTextBlock> StartBtnText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGFChatWidget> ChatUI;

	UFUNCTION()
	void PressedStartBtn();
	UFUNCTION()
	void PressedBackBtn();

	TObjectPtr<UGFChatWidget> GetChatUI() { return ChatUI; }
};
