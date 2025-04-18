#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Server/GFBasePlayerState.h"
#include "GF_FFAPlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGF_FFAPlayerState : public AGFBasePlayerState
{
	GENERATED_BODY()
	
public:

	// 서버 전체 공유
	static int32 TestPlayerIndex;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddKill();
	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetKillCount() const;

	// 테스트용 (PlayerName 초기화)
	virtual void BeginPlay() override;

protected:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Score")
	int32 KillCount = 0;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
};
