// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "GameFramework/PlayerController.h"
#include "GFPlayerController.generated.h"

struct FGameplayTag;
class UGFChatWidget;
class UInputAction;
class UInputMappingContext;

UCLASS()
class GLADIATORSFANTASY_API AGFPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	AGFPlayerController();
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|CharacterPawn")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|CharacterPawn")
	UInputAction* FocusChatChatAction;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFChatWidget> ChatWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UGFChatWidget> ChatWidget;

public:
	UFUNCTION(BlueprintCallable)
	UGFChatWidget* GetChatWidget() { return ChatWidget; }


	// ChatFunction
	UFUNCTION(Client, Reliable)
	void ClientReceiveMessage(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType = EMessage_Type::All);
	UFUNCTION(Server, Reliable)
	void ServerSendMessage(const FString& Message, const FString& TeamTagName, EMessage_Type MessageType);

	FString GetTeamTagName();
};
