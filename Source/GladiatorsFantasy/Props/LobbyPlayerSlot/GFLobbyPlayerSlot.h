#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "Props/LobbySelectedCharacter/GFLobbySelectedCharacter.h"
#include "GFLobbyPlayerSlot.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFLobbyPlayerSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFLobbyPlayerSlot();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Mesh")
	UStaticMeshComponent* StaticMeshCompo;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Property|Refs")
	APlayerController* PlayerController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Property|Refs", Replicated)
	AGFLobbySelectedCharacter* SelectedCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property|Spawn", Replicated)
	FString SlotNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property|Spawn", Replicated)
	FString AnimType;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterMesh)
	USkeletalMesh* ReplicatedMesh;
	UPROPERTY(ReplicatedUsing = OnRep_AnimSecquence)
	UAnimSequence* ReplicatedAnim;

	UFUNCTION()
	void OnRep_CharacterMesh();
	UFUNCTION()
	void OnRep_AnimSecquence();

	UFUNCTION(BlueprintCallable)
	void AddSelectedActor(APlayerController* In_PlayerController);
	UFUNCTION(BlueprintCallable)
	void RemoveSelectedActor();
	
	FString GetSlotNumber() { return SlotNumber; }
	APlayerController* GetPC() { return PlayerController; }
	// void SetPC(APlayerController* NewPlayerControllerler) { PlayerController = NewPlayerControllerler; }
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
