#include "Widget/CharacterSelectWidget/GFCharacterSelectWidget.h"

#include "Character/MainLoby/GFMainLobyPlayerController.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Server/GFBasePlayerState.h"

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
	if (InputNickName)
	{
		InputNickName->OnTextCommitted.AddDynamic(this, &UGFCharacterSelectWidget::OnTextCommitted);
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

	ConnectServer();
}

void UGFCharacterSelectWidget::ConnectServer()
{
	// 서버 주소 (예시 - 실제 주소로 변경)
	//FString ServerAddress = TEXT("127.0.0.1:7777");
    
	// 접속 요청시 옵션에 "?allowConnect" 추가하여 서버 PreLogin 검사를 통과하도록 함
	FString Options = TEXT("?allowConnect");

	// ClientTravel 호출 (APlayerController를 통해)
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		//PC->ClientTravel(ServerAddress + Options, TRAVEL_Absolute);
		PC->ClientTravel(Options, TRAVEL_Absolute, true);
	}
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

void UGFCharacterSelectWidget::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter)
	{
		APlayerController* PlayerController = GetOwningPlayer();
		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("NickName : %s"), *Text.ToString());
			PlayerController->GetPlayerState<AGFBasePlayerState>()->SetPlayerCustomName(Text.ToString());
		}
	}
}

void UGFCharacterSelectWidget::PressedNickNameSetBtn()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("NickName : %s"), *InputNickName->GetText().ToString());
		PlayerController->GetPlayerState<AGFBasePlayerState>()->SetPlayerCustomName(InputNickName->GetText().ToString());
	}
}
