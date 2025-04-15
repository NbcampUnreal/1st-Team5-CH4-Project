#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFDeadZoneActor.generated.h"

class UBoxComponent;

UCLASS()
class GLADIATORSFANTASY_API AGFDeadZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFDeadZoneActor();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerZone;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
