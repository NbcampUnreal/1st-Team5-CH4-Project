#pragma once

#include "CoreMinimal.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "GameFramework/GameState.h"
#include "GFBaseGameState.generated.h"

enum class EMessage_Type : uint8;

UCLASS()
class GLADIATORSFANTASY_API AGFBaseGameState : public AGameState
{
	GENERATED_BODY()

public:
	AGFBaseGameState();
	
	UFUNCTION(NetMulticast,Reliable)
	void BroadcastMessage(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType = EMessage_Type::All);
};