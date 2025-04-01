#include "ChatWidget/GFChatWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
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
	if (ChatAllLogBox)
	{
		for (int i = 0; i < 110; ++i)
		{
			FString Message = FString::Printf(TEXT("TestAll %d"), i);
			TObjectPtr<UTextBlock> NewMessage = NewMessageBlock(Message);
			if (NewMessage)
			{
				ChatAllLogBox->AddChild(NewMessage);
				ChatAllLogBox->ScrollToEnd();
			}
		}
	}

	if (ChatTeamLogBox)
	{
		FString Message = FString::Printf(TEXT("TestTeam"));
		TObjectPtr<UTextBlock> NewMessage = NewMessageBlock(Message);
		if (NewMessage)
		{
			ChatTeamLogBox->AddChild(NewMessage);
			ChatTeamLogBox->ScrollToEnd();
		}
	}

	if (ChatSystemLogBox)
	{
		FString Message = FString::Printf(TEXT("TestSystem"));
		TObjectPtr<UTextBlock> NewMessage = NewMessageBlock(Message);
		if (NewMessage)
		{
			ChatSystemLogBox->AddChild(NewMessage);
			ChatSystemLogBox->ScrollToEnd();
		}
	}
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
		NewMessage->Font.Size = FontSize;
		NewMessage->SetColorAndOpacity(FSlateColor(Color));
		NewMessage->SetText(FText::FromString(Message));
	}

	return NewMessage;
}

// ================================================
// Send Message Function
// ================================================
void UGFChatWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter && !Text.IsEmpty())
	{
		// AMultiBaseballController* Controller = Cast<AMultiBaseballController>(GetOwningPlayer());
		// if (Controller)
		// {
		// 	Controller->ServerSendMessage(Text.ToString());
		// }

		ChatInputBox->SetText(FText::GetEmpty());
	}
}