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

    UFUNCTION(Server, Reliable)
    void ServerSetReady(bool bReady);
    UFUNCTION(Client, Reliable)
    void ClientBlockInput(bool bBlock);


    virtual void BeginPlay() override;

protected:
    UPROPERTY()
    UGFShop* StoreWidget;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UGFShop> StoreWidgetClass;
};
