#pragma once

#include "CoreMinimal.h"
#include "Character/GFPlayerController.h"
#include "GFStorePlayerController.generated.h"

class UGFShop;

UCLASS()
class GLADIATORSFANTASY_API AGFStorePlayerController : public AGFPlayerController
{
	GENERATED_BODY()
	
public:
    UFUNCTION(Client, Reliable)
    void ClientShowStoreUI();

    UFUNCTION(Server, Reliable)
    void ServerSetReady(bool bReady);

protected:
    UPROPERTY()
    UGFShop* StoreWidget;
};
