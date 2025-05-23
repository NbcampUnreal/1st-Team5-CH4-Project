#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Server/GFBaseGameState.h"
#include "GFMainLobyPlayerController.generated.h"

class AGFLobbyPlayerSlot;
class UGFChatWidget;
class ASelectActor;
class UInputAction;
class UInputMappingContext;
class UGFLobyWidget;
class ULevelSequencePlayer;
class ALevelSequenceActor;
class ULevelSequence;
class UGFCharacterSelectWidget;
class ACineCameraActor;
class UGFMainLobyWidget;

UENUM()
enum class ESequenceType
{
	MainToSelect,
	SelectToMain,
	SelectToWaitRoom,
	WaitRoomToSelect,
	End
};

UCLASS()
class GLADIATORSFANTASY_API AGFMainLobyPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|CharacterPawn")
	UInputMappingContext* LobyMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input|CharacterPawn")
	UInputAction* SelectAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFMainLobyWidget> MainLobyWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UGFMainLobyWidget> MainLobyWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFCharacterSelectWidget> CharacterSelectWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UGFCharacterSelectWidget> CharacterSelectWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGFLobyWidget> LobyWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UGFLobyWidget> LobyWidget;

	// UPROPERTY(EditDefaultsOnly, Category = "UI")
	// TSubclassOf<UGFChatWidget> ChatWidgetClass;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	// TObjectPtr<UGFChatWidget> ChatWidget;
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<ACineCameraActor> MainCamera;
	
	UPROPERTY(EditDefaultsOnly, Category = "Cinematic")
	ULevelSequence* MainLobyToLobySequence;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematic")
	ALevelSequenceActor* MainLobyToLobySequenceActor;
	ULevelSequencePlayer* MainLobyToLobySequencePlayer;

	UPROPERTY(EditDefaultsOnly, Category = "Cinematic")
	ULevelSequence* SelectCharacterToWaitRoomSequence;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cinematic")
	ALevelSequenceActor* SelectCharacterToWaitRoomSequenceActor;
	ULevelSequencePlayer* SelectCharacterToWaitRoomSequencePlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LobbyProperty", Replicated)
	TObjectPtr<AGFLobbyPlayerSlot> LobbySlot;

	AGFMainLobyPlayerController();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSequenceFinished();
	
public:
	void ShowCharacterSelectWidget();
	void ShowMainLobyWidget();
	void ShowLobyWidget();
	
	void PlaySequnceSelectCharacterToMain();
	void PlaySequnceMainToSelectCharacter();
	void PlaySelectCharacterToWaitRoom();
	void PlayWaitRoomToSelectCharacter();

	void StopMainLobyToLobySequencePlayer();
	void StopSelectCharacterToWaitRoomSequencePlayer();

	void SetSequenceType(ESequenceType type) { CurrentSequenceType = type; }
	
	virtual void SetupInputComponent() override;
	void SelectActionTriggered();

	void SetSlot(AGFLobbyPlayerSlot* InSlot) { LobbySlot = InSlot; }

	UFUNCTION(Server, Reliable)
	void ServerSetMesh(const TSoftObjectPtr<USkeletalMesh>& InSkeletalMesh);
	UFUNCTION(Server, Reliable)
	void ServerSetAnim(const TSoftObjectPtr<UAnimSequence>& InAnimSequence);

	// ChatFunction
	UFUNCTION(Client, Reliable)
	void ClientReceiveMessage(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType = EMessage_Type::All);
	UFUNCTION(Server, Reliable)
	void ServerSendMessage(const FString& Message, const FString& TeamTagName, EMessage_Type MessageType);

	FString GetTeamTagName();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
private:
	ESequenceType CurrentSequenceType;
	TObjectPtr<ASelectActor> PrevSelectedWeapon;
	TObjectPtr<ASelectActor> PrevSelectedCharacter;

	void ChangeSelectedCharacter(FString SelecTypeTest);
	void ChangeAnim(FString SelecTypeTest);
};
