#include "Widget/LobyWidget/GFLobyWidget.h"

#include "Character/MainLoby/GFMainLobyPlayerController.h"
#include "Components/Button.h"
#include "Server/GFBaseGameMode.h"
#include "Server/GFBasePlayerState.h"

void UGFLobyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UGFLobyWidget::PressedStartBtn);
	}
	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UGFLobyWidget::PressedBackBtn);
	}
}

void UGFLobyWidget::PressedStartBtn()
{
	AGFBaseGameMode* GFGM = Cast<AGFBaseGameMode>(GetWorld()->GetAuthGameMode());
	GFGM->ChangeLevel();
}

void UGFLobyWidget::PressedBackBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		AGFMainLobyPlayerController* MainConroller = Cast<AGFMainLobyPlayerController>(PlayerController);
		if (MainConroller)
		{
			MainConroller->SetSequenceType(ESequenceType::WaitRoomToSelect);
			MainConroller->PlayWaitRoomToSelectCharacter();
		}
	}
	SetVisibility(ESlateVisibility::Hidden);
}
