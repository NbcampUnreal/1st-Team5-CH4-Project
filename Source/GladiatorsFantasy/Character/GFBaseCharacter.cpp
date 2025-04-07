#include "GFBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "GFPlayerController.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "Component/MultiplayerEventsManager/GFMultiplayerEventsManager.h"

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

FString AGFBaseCharacter::GetTeamTagName()
{
	// 이미 액터에 부착된 컴포넌트 목록에서 찾기
	TArray<UActorComponent*> Components;
	GetComponents(Components);
	for (UActorComponent* Comp : Components)
	{
		if (Comp && Comp->GetClass()->GetName().Contains(TEXT("BPC_MultiplayerEventsManager")))
		{
			TObjectPtr<UGFMultiplayerEventsManager> MulitPlayerComponent = Cast<UGFMultiplayerEventsManager>(Comp);
			if (MulitPlayerComponent)
			{
				return MulitPlayerComponent->GetCurrentTeamTagName();
			}
		}
	}

	return "Error";
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

