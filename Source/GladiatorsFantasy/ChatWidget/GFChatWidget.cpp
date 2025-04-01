#include "ChatWidget/GFChatWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"


void UGFChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ChatMoveBtn)
	{
		ChatMoveBtn->OnPressed.AddDynamic(this, &UGFChatWidget::DragChatMoveBtn);
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

void UGFChatWidget::DragChatMoveBtn()
{
}

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
		case All:
			ChatLogBoxSwitcher->SetActiveWidgetIndex(All);
			break;
			
		case Team:
			ChatLogBoxSwitcher->SetActiveWidgetIndex(Team);
			break;
		
		case System:
			ChatLogBoxSwitcher->SetActiveWidgetIndex(System);
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
