#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFChatWidget.generated.h"

class UTextBlock;
class UEditableText;
class UWidgetSwitcher;
class UButton;
class UScrollBox;
class UEditableTextBox;

UENUM()
enum EFilter_Type
{
	All,
	Team,
	System,
	End
};

UCLASS()
class GLADIATORSFANTASY_API UGFChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> ChatInputBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> ChatLogBoxSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ChatMoveBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FilterAllBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FilterTeamBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> FilterSystemBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatAllLogBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatTeamLogBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScrollBox> ChatSystemLogBox;

	UFUNCTION()
	void DragChatMoveBtn();
	
	UFUNCTION()
	void ClickOnFilterAllBtn();
	UFUNCTION()
	void ClickOnFilterTeamBtn();
	UFUNCTION()
	void ClickOnFilterSystemBtn();

	UFUNCTION()
	void SwitchLogBox(EFilter_Type Type);

private:
	UTextBlock* NewMessageBlock(const FString& Message, int FontSize = 15.0f, FLinearColor Color = FLinearColor::White);
};