
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFApple.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFApple : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFApple();

protected:
	virtual void BeginPlay() override;

	// 충돌 시 호출
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
	// 스턴 지속 시간 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stun")
	float StunDuration;

	// 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AppleMesh;

	// 아이템이 캐릭터에 장착되었는지 여부
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	bool bIsEquipped;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void PickUp(ACharacter* NewOwner);

	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void Throw(FVector ThrowImpulse);
};
