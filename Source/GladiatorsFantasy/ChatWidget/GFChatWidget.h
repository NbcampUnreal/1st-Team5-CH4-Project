#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFChatWidget.generated.h"

class UCanvasPanel;
class UScaleBox;
class UTextBlock;
class UEditableText;
class UWidgetSwitcher;
class UButton;
class UScrollBox;
class UEditableTextBox;

UENUM()
enum class EFilter_Type
{
	All,
	Team,
	System,
	End
};

UENUM()
enum class EScaleBtn_Type
{
	Right,
	Bottom,
	RightBottom,
	End
};

UENUM()
enum class EMessage_Type :uint8
{
	All UMETA(DisplayName = "All"),
	Team UMETA(DisplayName = "Team"),
	System UMETA(DisplayName = "System"),
	End,
};

UCLASS()
class GLADIATORSFANTASY_API UGFChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScaleBox> ChatScaleBox;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> ChatCanvasPanel;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MessageTypeText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> ChatInputBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> ChatLogBoxSwitcher;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ChatMoveBtn;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ScaleDownBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ScaleLeftBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ScaleLeftDownBtn;
	
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
	void PressedChatMoveBtn();
	UFUNCTION()
	void ReleasedChatMoveBtn();

	UFUNCTION()
	void PressedScaleDownBtn();
	UFUNCTION()
	void ReleasedScaleDownBtn();
	UFUNCTION()
	void PressedScaleRightBtn();
	UFUNCTION()
	void ReleasedScaleRightBtn();
	UFUNCTION()
	void PressedScaleRightDownBtn();
	UFUNCTION()
	void ReleasedScaleRightDownBtn();
	
	
	UFUNCTION()
	void ClickOnFilterAllBtn();
	UFUNCTION()
	void ClickOnFilterTeamBtn();
	UFUNCTION()
	void ClickOnFilterSystemBtn();

	UFUNCTION()
	void SwitchLogBox(EFilter_Type Type);
	
	UFUNCTION()
	void DragChatUI();
	UFUNCTION()
	void DragChatUIScale();

	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	UFUNCTION()
	void UpdateMessageTypeText();
	
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	
private:
	UTextBlock* NewMessageBlock(const FString& Message, int FontSize = 15.0f, FLinearColor Color = FLinearColor::White);
	void SetScaleTimerHandle();
	void ClearScaleTimerHandle() { 	GetWorld()->GetTimerManager().ClearTimer(ScaleTimerHandle);};
	void SwitchChatMode();
	
	FVector2d PrevMousePos;
	FTimerHandle DragTimerHandle;
	FTimerHandle ScaleTimerHandle;
	FVector2d MinChatUISize;
	
	EScaleBtn_Type CurrentScaleBtnType;
	EMessage_Type CurrentMessageType;
};
