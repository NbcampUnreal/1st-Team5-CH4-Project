#include "Widget/LobyWidget/GFLobyWidget.h"

#include "Character/MainLoby/GFMainLobyPlayerController.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Server/GFBaseGameMode.h"
#include "Server/GFBasePlayerState.h"

void UGFLobyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (StartBtn)
	{
		if (APlayerController* PlayerController = GetOwningPlayer())
		{
			if (!PlayerController->HasAuthority())
			{
				// Ready로 수정
				// if (StartBtnText)
				// {
				// 	StartBtnText->SetText(FText::FromString("준비"));
				// }
				StartBtn->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				StartBtn->OnClicked.AddDynamic(this, &UGFLobyWidget::PressedStartBtn);
			}
		}
	}
	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UGFLobyWidget::PressedBackBtn);
	}
}

void UGFLobyWidget::PressedStartBtn()
{
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (PlayerController->HasAuthority())
		{
			AGFBaseGameMode* GFGM = Cast<AGFBaseGameMode>(GetWorld()->GetAuthGameMode());
			GFGM->ChangeLevel();
		}
	}
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
