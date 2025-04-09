#pragma once

#include "CoreMinimal.h"
#include "Server/GFBaseGameMode.h"
#include "GFMainLobyGameMode.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFMainLobyGameMode : public AGFBaseGameMode
{
	GENERATED_BODY()
	
public:
	virtual FString GetTargetMapName() const override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
