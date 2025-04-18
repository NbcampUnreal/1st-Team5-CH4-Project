#pragma once

#include "CoreMinimal.h"
#include "Server/GFBaseGameMode.h"
#include "GFMainLobyGameMode.generated.h"

class AGFLobbyPlayerSlot;

UCLASS()
class GLADIATORSFANTASY_API AGFMainLobyGameMode : public AGFBaseGameMode
{
	GENERATED_BODY()

public:
	TArray<AGFLobbyPlayerSlot*> PlayerSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsSetPlayerSlotsDone;

	AGFMainLobyGameMode();
	
	virtual FString GetTargetMapName() const override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	void SetPlayerSlot();

	void BeginPlay() override;

private:
	FTimerHandle TimerHandle_UpdateSlots;
};
