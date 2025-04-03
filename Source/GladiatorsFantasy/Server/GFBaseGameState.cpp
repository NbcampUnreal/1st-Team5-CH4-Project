#include "Server/GFBaseGameState.h"

#include "Character/GFPlayerController.h"

AGFBaseGameState::AGFBaseGameState()
{
}

void AGFBaseGameState::BroadcastMessage_Implementation(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType)
{
	FString FullMessage = FString::Printf(TEXT("[%s]: %s"), *SenderName, *Message);

	APlayerController* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		AGFPlayerController* PlayerController = Cast<AGFPlayerController>(LocalController);
		if (PlayerController)
		{
			PlayerController->ClientReceiveMessage(SenderName, TeamTagName, FullMessage, MessageType);
		}
	}
}