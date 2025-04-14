#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameInstance/GFGameInstance.h"
#include "Weapon/GFWeaponBase.h"
#include "GFBasePlayerState.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFBasePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Player")
	FString GetPlayerUniqueId() const;

    UFUNCTION(BlueprintCallable, Category = "Character")
    TSubclassOf<ACharacter> GetCharacterClassFromBPName() const;

    UFUNCTION(BlueprintCallable)
	void SaveToGameInstance(); 
    UFUNCTION(BlueprintCallable)
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
    UFUNCTION(BlueprintCallable)
    FString GetCharacterBPName() const;
    UFUNCTION(BlueprintCallable)
    FWeaponInfo GetWeaponInfo() const;

    // Setter
    UFUNCTION(BlueprintCallable)
    void SetPlayerCustomName(const FString& CustomName);
    UFUNCTION(BlueprintCallable)
    void SetMoney(int32 InMoney);
    UFUNCTION(BlueprintCallable)
    void SetWinPoint(int32 InWinPoint);
    UFUNCTION(BlueprintCallable)
    void SetCharacterBPName(const FString& InCharacterBPName);
    UFUNCTION(BlueprintCallable)
    void SetFWeaponInfo(const FString& InWeaponName, EWeaponRarity InRarity);

    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetPlayerCustomName(const FString& CustomName);
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetMoney(int32 InMoney);
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetWinPoint(int32 InWinPoint);
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetCharacterBPName(const FString& InCharacterBPName);
    UFUNCTION(BlueprintCallable, Server, Reliable)
    void ServerSetFWeaponInfo(const FString& InWeaponName, EWeaponRarity InRarity);

    virtual void PostNetInit() override;
    virtual void BeginPlay() override;
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    // 테스트용
    virtual void Tick(float DeltaSeconds) override;
    void CheckPlayerIdDelayed();
    UFUNCTION(BlueprintCallable)
    void LogPlayerStateData(FString CallerTag);

protected:
    UPROPERTY(Replicated)
    FString PlayerCustomName;

    UPROPERTY(Replicated)
    int32 Money;

    UPROPERTY(Replicated)
    int32 WinPoint;

    UPROPERTY(Replicated)
    int32 LossCount;

    UPROPERTY(Replicated)
    FString CharacterBPName;

    UPROPERTY(Replicated)
    FWeaponInfo WeaponInfo;

    UPROPERTY(EditDefaultsOnly, Category = "Character")
    UDataTable* CharacterDataTable;
};
