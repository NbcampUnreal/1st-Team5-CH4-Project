#include "GFBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "GFPlayerController.h"
#include "ChatWidget/GFChatWidget.h"

AGFBaseCharacter::AGFBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGFBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGFBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGFBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput
		= Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AGFPlayerController* PlayerController
			= Cast<AGFPlayerController>(GetController()))
		{
			if (PlayerController->FocusChatChatAction)
			{
				EnhancedInput->BindAction(PlayerController->FocusChatChatAction
					, ETriggerEvent::Triggered
					,this
					, &AGFBaseCharacter::FocusChatInputBox);
			}
		}
	}
}

void AGFBaseCharacter::FocusChatInputBox(const FInputActionValue& Value)
{
	if (AGFPlayerController* PlayerController = Cast<AGFPlayerController>(GetController()))
	{
		if (TObjectPtr<UGFChatWidget> ChatWidget = PlayerController->GetChatWidget())
		{
			if (ChatWidget->ChatInputBox)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				ChatWidget->SetChatInputBoxFocus();
			}
		}
	}
}

