// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "Widget/DOMGameWidget/GFCaptureStatusWidget.h"
#include "Widget/TDMGameWidget/GFTDMStatusWidget.h"
#include "GameFramework/PlayerController.h"
#include "GFPlayerController.generated.h"

struct FGameplayTag;
class UGFChatWidget;
class UInputAction;
class UInputMappingContext;
class UGFCaptureStatusWidget;

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
	TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TObjectPtr<UUserWidget> MainWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> SkillWidget;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFChatWidget> ChatWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UGFChatWidget> ChatWidget;

	// 점령전 변수
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFCaptureStatusWidget> GFCaptureStatusWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UGFCaptureStatusWidget> GFCaptureStatusWidget;

	// 데스매치 변수
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFTDMStatusWidget> GFTDMStatusWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UGFTDMStatusWidget> GFTDMStatusWidget;

public:
	UFUNCTION(BlueprintCallable)
	UGFChatWidget* GetChatWidget() { return ChatWidget; }
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetSkillWidget() { return SkillWidget; }
	UFUNCTION(BlueprintCallable)
	UGFCaptureStatusWidget* GetGFCaptureStatusWidget() { return GFCaptureStatusWidget; }


	// ChatFunction
	UFUNCTION(Client, Reliable)
	void ClientReceiveMessage(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType = EMessage_Type::All);
	UFUNCTION(Server, Reliable)
	void ServerSendMessage(const FString& Message, const FString& TeamTagName, EMessage_Type MessageType);

	FString GetTeamTagName();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_Pawn() override;
};
