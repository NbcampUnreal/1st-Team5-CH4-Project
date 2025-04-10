
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGFChicken.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AAGFChicken : public AActor
{
	GENERATED_BODY()
	
public:
	AAGFChicken();

protected:
	virtual void BeginPlay() override;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ChickenMesh;

	// 던질 때 재생할 소리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* ThrowSound;

	// 아이템이 캐릭터에 장착되었는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bIsEquipped;

	// 캐릭터에 아이템을 장착하는 함수
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void PickUp(ACharacter* NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void Throw(FVector ThrowImpulse);
};
