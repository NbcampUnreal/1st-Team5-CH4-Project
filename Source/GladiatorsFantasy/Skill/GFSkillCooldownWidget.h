// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFSkillCooldownWidget.generated.h"

class UGFSkillCooldownWidgetSlot;
enum class EWeaponRarity : uint8;

UCLASS()
class GLADIATORSFANTASY_API UGFSkillCooldownWidget : public UUserWidget
{
	GENERATED_BODY()

public: 
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	TArray<UGFSkillCooldownWidgetSlot*> GetCooldownSlots() const;
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void AddCooldownSlots(UGFSkillCooldownWidgetSlot* CooldownSlot);
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void ActivateSkills();
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void InitAllSkillActivate(bool bIsActivate);
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void SetSkillSlotRarity();

	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	FName GetCurrentWeaponName() const { return CurrentWeaponName; }
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void SetCurrentWeaponName(FName NewWeaponName) { CurrentWeaponName = NewWeaponName; }
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	EWeaponRarity GetWeaponRarityType() const { return WeaponRarityType; }
	UFUNCTION(BlueprintCallable, Category = "Cooldown")
	void SetWeaponRarityType(EWeaponRarity NewRarityType) { WeaponRarityType = NewRarityType; }

private:
	TArray<UGFSkillCooldownWidgetSlot*> CooldownSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeaponRarity WeaponRarityType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName CurrentWeaponName;

};
