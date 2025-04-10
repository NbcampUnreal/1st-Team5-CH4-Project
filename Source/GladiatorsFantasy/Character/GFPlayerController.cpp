#include "GFPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "GFBaseCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "Server/GFBaseGameState.h"
#include "Server/GFBasePlayerState.h"


AGFPlayerController::AGFPlayerController()
{
	bReplicates = true;
}

void AGFPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(this))
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				if (nullptr != DefaultMappingContext)
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}

	// Widget Test Code
	if (IsLocalController())
	{
		ChatWidget = CreateWidget<UGFChatWidget>(this, ChatWidgetClass);
		if (ChatWidget)
		{
			ChatWidget->AddToViewport();
		}
	}
}

FString AGFPlayerController::GetTeamTagName()
{
	TObjectPtr<AGFBaseCharacter> PlayerCharacter = Cast<AGFBaseCharacter>(GetPawn());
	
	if (PlayerCharacter)
	{
		return PlayerCharacter->GetTeamTagName();
	}
	
	return "Error";
}

// ================================================
// Chat Function
// ================================================
void AGFPlayerController::ClientReceiveMessage_Implementation(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType)
{
	if (ChatWidget)
	{
		if (MessageType == EMessage_Type::Team
			&& TeamTagName != GetTeamTagName())
		{
				return;
		}
		
		ChatWidget->UpdateChatLogBox(Message, MessageType);
	}
}

void AGFPlayerController::ServerSendMessage_Implementation(const FString& Message, const FString& TeamTagName, EMessage_Type MessageType)
{
	TObjectPtr<AGFBaseGameState> BaseGameState = GetWorld()->GetGameState<AGFBaseGameState>();
	if (BaseGameState)
	{
		BaseGameState->BroadcastMessage(GetPlayerState<AGFBasePlayerState>()->GetPlayerCustomName(), TeamTagName, Message, MessageType);
	}
}