#pragma once

#include "CoreMinimal.h"
#include "Server/GFBaseGameMode.h"
#include "GF_FFAGameMode.generated.h"

class AGFPlayerController;
class AGF_FFAPlayerState;
class AGF_FFAGameState;
class AGFAIController;
class AAIController;

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAGameMode : public AGFBaseGameMode
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Spawning")
	FTransform GetAvailablePlayerStartTransform();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Spawning")
	FTransform GetRandomPlayerStartTransform() const;

	// 테스트용
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    // 현재 사용된 PlayerStart 목록
    UPROPERTY()
    TArray<AActor*> UsedPlayerStarts;
	
};
