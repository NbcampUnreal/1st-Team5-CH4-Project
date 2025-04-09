#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFCaptureZone.generated.h"

class UBoxComponent;

UCLASS()
class GLADIATORSFANTASY_API AGFCaptureZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AGFCaptureZone();

protected:
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CaptureBox")
	UBoxComponent* CaptureBox;

	

	// 초당 게이지 변화량
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gauge")
	float CaptureRatePerSecond = 5.f;

	// 시간 추적용
	float LastEvaluateTime = 0.f;

	

private:
	TSet<AActor*> PlayersInZone;
	FTimerHandle CaptureEvaluationTimer;

	UFUNCTION()
	void EvaluateCaptureStatus();

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	

	// 테스트용 로깅 함수
	void LogPlayerTeamInfo(const TMap<FName, int32>& TeamCounts, float GaugeToPrint);
};
