
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFBanana.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFBanana : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFBanana();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:	
	// 미끄러짐의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Banana")
	float SlipImpulseMagnitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BananaMesh;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void PickUp(ACharacter* NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void Throw(FVector ThrowImpulse);
};
