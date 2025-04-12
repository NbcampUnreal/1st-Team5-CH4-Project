#pragma once

#include "CoreMinimal.h"
#include "Server/GFBasePlayerState.h"
#include "GFStorePlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFStorePlayerState : public AGFBasePlayerState
{
	GENERATED_BODY()
public:

	UPROPERTY(Replicated)
	bool bIsReady = false;

	void SetIsReady(bool b) { bIsReady = b; }

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

};
