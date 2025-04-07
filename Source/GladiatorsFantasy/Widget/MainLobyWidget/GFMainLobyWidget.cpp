#include "Widget/MainLobyWidget/GFMainLobyWidget.h"
#include "Character/MainLoby/GFMainLobyPlayerController.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widget/CharacterSelectWidget/GFCharacterSelectWidget.h"

class ULevelSequencePlayer;

void UGFMainLobyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UGFMainLobyWidget::PressedStartBtn);
	}
	if (SettingBtn)
	{
		SettingBtn->OnClicked.AddDynamic(this, &UGFMainLobyWidget::PressedStartBtn);
	}
	if (CreditsBtn)
	{
		CreditsBtn->OnClicked.AddDynamic(this, &UGFMainLobyWidget::PressedStartBtn);
	}
	if (ExitBtn)
	{
		ExitBtn->OnClicked.AddDynamic(this, &UGFMainLobyWidget::PressedExitBtn);
	}
}

void UGFMainLobyWidget::PressedStartBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		AGFMainLobyPlayerController* MainConroller = Cast<AGFMainLobyPlayerController>(PlayerController);
		if (MainConroller)
		{
			MainConroller->SetSequenceType(ESequenceType::MainToSelect);
			MainConroller->PlaySequnceMainToSelectCharacter();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}

void UGFMainLobyWidget::PressedSettingBtn()
{
	
}

void UGFMainLobyWidget::PressedCreditsBtn()
{
	
}

void UGFMainLobyWidget::PressedExitBtn()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(),EQuitPreference::Quit,false);
}