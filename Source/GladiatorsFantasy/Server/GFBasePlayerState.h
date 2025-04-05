#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GFBasePlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFBasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Player")
	FString GetPlayerUniqueId() const;

	void SaveToGameInstance(); 
	void LoadFromGameInstance(); 

    // Getter
    UFUNCTION(BlueprintCallable)
    FString GetPlayerCustomName() const;

    UFUNCTION(BlueprintCallable)
    int32 GetMoney() const;

    UFUNCTION(BlueprintCallable)
    int32 GetWinPoint() const;

    UFUNCTION(BlueprintCallable)
    int32 GetLossCount() const;

    // Setter
    UFUNCTION(BlueprintCallable)
    void SetPlayerCustomName(FString CustomName);

    virtual void PostNetInit() override;
    virtual void BeginPlay() override;
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    // 테스트용
    virtual void Tick(float DeltaSeconds) override;
    void CheckPlayerIdDelayed();

private:
    UPROPERTY(Replicated)
    FString PlayerCustomName;

    UPROPERTY(Replicated)
    int32 Money;

    UPROPERTY(Replicated)
    int32 WinPoint;

    UPROPERTY(Replicated)
    int32 LossCount;

};
