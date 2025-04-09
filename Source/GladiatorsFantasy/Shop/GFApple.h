
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

public:	
	// 스턴 지속 시간 (초)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stun")
	float StunDuration;

	// 메시 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AppleMesh;

};
