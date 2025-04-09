
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

public:	
	// 미끄러짐의 강도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Banana")
	float SlipImpulseMagnitude;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BananaMesh;

};
