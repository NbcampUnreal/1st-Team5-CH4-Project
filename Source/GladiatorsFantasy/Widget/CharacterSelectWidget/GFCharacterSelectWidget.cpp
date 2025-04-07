#include "Widget/CharacterSelectWidget/GFCharacterSelectWidget.h"

#include "Character/MainLoby/GFMainLobyPlayerController.h"
#include "Components/Button.h"

void UGFCharacterSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NextBtn)
	{
		NextBtn->OnClicked.AddDynamic(this, &UGFCharacterSelectWidget::PressedNextBtn);
	}
	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UGFCharacterSelectWidget::PressedBackBtn);
	}
	if (NickNameSetBtn)
	{
		NickNameSetBtn->OnClicked.AddDynamic(this, &UGFCharacterSelectWidget::PressedNickNameSetBtn);
	}
}

void UGFCharacterSelectWidget::PressedNextBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		AGFMainLobyPlayerController* MainConroller = Cast<AGFMainLobyPlayerController>(PlayerController);
		if (MainConroller)
		{
			MainConroller->StopMainLobyToLobySequencePlayer();
			MainConroller->SetSequenceType(ESequenceType::SelectToWaitRoom);
			MainConroller->PlaySelectCharacterToWaitRoom();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UGFCharacterSelectWidget::PressedBackBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		AGFMainLobyPlayerController* MainConroller = Cast<AGFMainLobyPlayerController>(PlayerController);
		if (MainConroller)
		{
			MainConroller->StopSelectCharacterToWaitRoomSequencePlayer();
			MainConroller->SetSequenceType(ESequenceType::SelectToMain);
			MainConroller->PlaySequnceSelectCharacterToMain();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UGFCharacterSelectWidget::PressedNickNameSetBtn()
{
}
