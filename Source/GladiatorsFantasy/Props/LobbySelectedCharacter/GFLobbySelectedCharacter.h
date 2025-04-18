#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFLobbySelectedCharacter.generated.h"

class AGFLobbyPlayerSlot;

UCLASS()
class GLADIATORSFANTASY_API AGFLobbySelectedCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFLobbySelectedCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components|Mesh")
	USkeletalMeshComponent* SkeletalMeshCompo;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Property|Refs", Replicated)
	//AGFLobbyPlayerSlot* OwnerSlot;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
