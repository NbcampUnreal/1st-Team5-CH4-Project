#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFShopCharacterActor.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFShopCharacterActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AGFShopCharacterActor();

protected:

	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* MeshComponent;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterMesh)
	TSoftObjectPtr<USkeletalMesh> ReplicatedMesh;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterAnim)
	TSoftObjectPtr<UAnimSequence> ReplicatedAnim;

	UPROPERTY(EditAnywhere, Category = "Character Data")
	UDataTable* StoreCharacterDataTable;

	UFUNCTION()
	void OnRep_CharacterMesh();

	UFUNCTION()
	void OnRep_CharacterAnim();

	void SetupCharacterMesh(const FString& CharacterBPName);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
