#include "Widget/ChatWidget/GFChatWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Character/GFPlayerController.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/EditableText.h"
#include "Components/ScaleBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"


void UGFChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MinChatUISize = FVector2D(380.0f, 90.0f);
	CurrentMessageType = EMessage_Type::All;
	
	if (ChatMoveBtn)
	{
		ChatMoveBtn->OnPressed.AddDynamic(this, &UGFChatWidget::PressedChatMoveBtn);
		ChatMoveBtn->OnReleased.AddDynamic(this, &UGFChatWidget::ReleasedChatMoveBtn);
	}

	if (ScaleDownBtn)
	{
		ScaleDownBtn->OnPressed.AddDynamic(this, &UGFChatWidget::PressedScaleDownBtn);
		ScaleDownBtn->OnReleased.AddDynamic(this, &UGFChatWidget::ReleasedScaleDownBtn);
	}
	if (ScaleLeftBtn)
	{
		ScaleLeftBtn->OnPressed.AddDynamic(this, &UGFChatWidget::PressedScaleRightBtn);
		ScaleLeftBtn->OnReleased.AddDynamic(this, &UGFChatWidget::ReleasedScaleRightBtn);
	}
	if (ScaleLeftDownBtn)
	{
		ScaleLeftDownBtn->OnPressed.AddDynamic(this, &UGFChatWidget::PressedScaleRightDownBtn);
		ScaleLeftDownBtn->OnReleased.AddDynamic(this, &UGFChatWidget::ReleasedScaleRightDownBtn);
	}
	
	if (FilterAllBtn)
	{
		FilterAllBtn->OnClicked.AddDynamic(this, &UGFChatWidget::ClickOnFilterAllBtn);
	}
	if (FilterTeamBtn)
	{
		FilterTeamBtn->OnClicked.AddDynamic(this, &UGFChatWidget::ClickOnFilterTeamBtn);
	}
	if (FilterSystemBtn)
	{
		FilterSystemBtn->OnClicked.AddDynamic(this, &UGFChatWidget::ClickOnFilterSystemBtn);
	}

	if (ChatInputBox)
	{
		ChatInputBox->OnTextCommitted.AddDynamic(this, &UGFChatWidget::OnTextCommitted);
	}


	// TestCode
	SetIsFocusable(true);
	UpdateMessageTypeText();
}

// ================================================
// UI Move Function
// ================================================
void UGFChatWidget::PressedChatMoveBtn()
{
	PrevMousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	GetWorld()->GetTimerManager().SetTimer(DragTimerHandle, this, &UGFChatWidget::DragChatUI, 0.01f, true);
}

void UGFChatWidget::ReleasedChatMoveBtn()
{
	GetWorld()->GetTimerManager().ClearTimer(DragTimerHandle);
}

void UGFChatWidget::DragChatUI()
{
	FVector2D MousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D MouseDelta = MousePos - PrevMousePos;
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatScaleBox);
	if (CanvasSlot)
	{
		FVector2D WidgetPos = CanvasSlot->GetPosition();
		CanvasSlot->SetPosition(WidgetPos + MouseDelta);
	}
	PrevMousePos = MousePos;
}

// ================================================
// UI Scaling Function
// ================================================
void UGFChatWidget::PressedScaleDownBtn()
{
	CurrentScaleBtnType = EScaleBtn_Type::Bottom;
	SetScaleTimerHandle();
}

void UGFChatWidget::ReleasedScaleDownBtn()
{
	ClearScaleTimerHandle();
}

void UGFChatWidget::PressedScaleRightBtn()
{
	CurrentScaleBtnType = EScaleBtn_Type::Right;
	SetScaleTimerHandle();
}

void UGFChatWidget::ReleasedScaleRightBtn()
{
	ClearScaleTimerHandle();
}

void UGFChatWidget::PressedScaleRightDownBtn()
{
	CurrentScaleBtnType = EScaleBtn_Type::RightBottom;
	SetScaleTimerHandle();
}

void UGFChatWidget::ReleasedScaleRightDownBtn()
{
	ClearScaleTimerHandle();
}

void UGFChatWidget::SetScaleTimerHandle()
{
	PrevMousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	GetWorld()->GetTimerManager().SetTimer(ScaleTimerHandle, this, &UGFChatWidget::DragChatUIScale, 0.01f, true);
}

void UGFChatWidget::DragChatUIScale()
{
	FVector2D CurrentMousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(ChatScaleBox);
	if (CanvasSlot)
	{
		FVector2D Delta = FVector2d::Zero();
		switch (CurrentScaleBtnType)
		{
			case EScaleBtn_Type::Right:
				Delta.X = CurrentMousePos.X - PrevMousePos.X;
				break;
			
			case EScaleBtn_Type::Bottom:
				Delta.Y = CurrentMousePos.Y - PrevMousePos.Y;
				break;

			case EScaleBtn_Type::RightBottom:
				Delta = CurrentMousePos - PrevMousePos;
				break;
			
			default:
				break;
		}

		FVector2D NewSize = CanvasSlot->GetSize() + Delta;
		if (NewSize.X < MinChatUISize.X)
			NewSize.X = MinChatUISize.X;
		if (NewSize.Y < MinChatUISize.Y)
			NewSize.Y = MinChatUISize.Y;
		CanvasSlot->SetSize(NewSize);

		PrevMousePos = CurrentMousePos;
	}
}

// ================================================
// UI Filter Function
// ================================================
void UGFChatWidget::ClickOnFilterAllBtn()
{
	SwitchLogBox(EFilter_Type::All);
}

void UGFChatWidget::ClickOnFilterTeamBtn()
{
	SwitchLogBox(EFilter_Type::Team);
}

void UGFChatWidget::ClickOnFilterSystemBtn()
{
	SwitchLogBox(EFilter_Type::System);
}

void UGFChatWidget::SwitchLogBox(EFilter_Type Type)
{
	if (!ChatLogBoxSwitcher)
		return;
	
	switch (Type)
	{
		case EFilter_Type::All:
			ChatLogBoxSwitcher->SetActiveWidgetIndex((UINT)EFilter_Type::All);
			break;
			
		case EFilter_Type::Team:
			ChatLogBoxSwitcher->SetActiveWidgetIndex((UINT)EFilter_Type::Team);
			break;
		
		case EFilter_Type::System:
			ChatLogBoxSwitcher->SetActiveWidgetIndex((UINT)EFilter_Type::System);
			break;
		
		default:
			break;
	}
}

UTextBlock* UGFChatWidget::NewMessageBlock(const FString& Message, int FontSize, FLinearColor Color)
{
	UTextBlock* NewMessage = NewObject<UTextBlock>(this);

	if (NewMessage)
	{
		// NewMessage->Font.Size = FontSize;
		// NewMessage->SetColorAndOpacity(FSlateColor(Color));
		// NewMessage->SetText(FText::FromString(Message));

		FSlateFontInfo FontInfo;
		FontInfo.Size = FontSize;
		FontInfo.FontObject = LoadObject<UObject>(nullptr, TEXT("/Script/Engine.Font'/Game/SH/Font/Pretendard-Thin_Font.Pretendard-Thin_Font'")); 

		NewMessage->SetColorAndOpacity(FSlateColor(Color));
		NewMessage->SetFont(FontInfo);
		NewMessage->SetText(FText::FromString(Message));
	}

	return NewMessage;
}

// ================================================
// Send Message Function
// ================================================
void UGFChatWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter)
	{
		AGFPlayerController* Controller = Cast<AGFPlayerController>(GetOwningPlayer());
		if (Controller)
		{
			if (!Text.IsEmpty())
			{
				FString TeamTag = Controller->GetTeamTagName();
				Controller->ServerSendMessage(Text.ToString(), TeamTag, CurrentMessageType);
			}
		}

		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
		ChatInputBox->SetText(FText::GetEmpty());
		FSlateApplication::Get().ClearKeyboardFocus();
	}
}

FReply UGFChatWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey PressedKey = InKeyEvent.GetKey();
    
	if (PressedKey == EKeys::Tab)
	{
		SwitchChatMode();
        
		return FReply::Handled();
	}

	return Super::NativeOnPreviewKeyDown(InGeometry, InKeyEvent);
}

void UGFChatWidget::SwitchChatMode()
{
	CurrentMessageType = (EMessage_Type)((((int)CurrentMessageType)+1)%(int)EMessage_Type::System);
	UpdateMessageTypeText();
}

void UGFChatWidget::UpdateMessageTypeText()
{
	if (!MessageTypeText)
		return;
	
	FString EnumToString = TEXT("Invalid");
	const UEnum* CharStateEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EMessage_Type"), true);
	if (CharStateEnum)
	{
		EnumToString = CharStateEnum->GetNameStringByValue((int64)CurrentMessageType);
	}
	
	FString Message = FString::Printf(TEXT("[%s]:"), *EnumToString);
	MessageTypeText->SetText(FText::FromString(Message));
}

void UGFChatWidget::SetChatInputBoxFocus()
{
	ChatInputBox->SetKeyboardFocus();
}

bool UGFChatWidget::IsFocusOnChatInputBox()
{
	bool result = false;
	if (ChatInputBox && ChatInputBox->HasKeyboardFocus())
	{
		result = true;
	}

	return result;
}

// ================================================
// Update UI Function
// ================================================
void UGFChatWidget::UpdateChatLogBox(const FString& Message, EMessage_Type MessageType)
{
	switch (MessageType)
	{
	case EMessage_Type::All:
			UpdateChatAllLogBox(Message, 13, FLinearColor::White);
			break;
		
		case EMessage_Type::Team:
			UpdateChatAllLogBox(Message, 13, FLinearColor::Blue);
			UpdateChatTeamLogBox(Message, 13, FLinearColor::Blue);
			break;
		
		case EMessage_Type::System:
			UpdateChatAllLogBox(Message, 13, FLinearColor::Yellow);
			UpdateChatTeamLogBox(Message, 13, FLinearColor::Yellow);
			UpdateChatSystemLogBox(Message, 13, FLinearColor::Yellow);
			break;
		
		default:
			break;
	}
}

void UGFChatWidget::UpdateChatAllLogBox(const FString& Message, int FontSize, FLinearColor Color)
{
	TObjectPtr<UTextBlock> MessageBlock = NewMessageBlock(Message, FontSize, Color);
	if (MessageBlock)
	{
		ChatAllLogBox->AddChild(MessageBlock);
		ChatAllLogBox->ScrollToEnd();
	}
}

void UGFChatWidget::UpdateChatTeamLogBox(const FString& Message, int FontSize, FLinearColor Color)
{
	TObjectPtr<UTextBlock> MessageBlock = NewMessageBlock(Message, FontSize, Color);
	if (MessageBlock)
	{
		ChatTeamLogBox->AddChild(MessageBlock);
		ChatTeamLogBox->ScrollToEnd();
	}
}

void UGFChatWidget::UpdateChatSystemLogBox(const FString& Message, int FontSize, FLinearColor Color)
{
	TObjectPtr<UTextBlock> MessageBlock = NewMessageBlock(Message, FontSize, Color);
	if (MessageBlock)
	{
		ChatSystemLogBox->AddChild(MessageBlock);
		ChatSystemLogBox->ScrollToEnd();
	}
}