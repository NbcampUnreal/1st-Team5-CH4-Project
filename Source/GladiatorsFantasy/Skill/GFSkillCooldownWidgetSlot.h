// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFSkillCooldownWidgetSlot.generated.h"

class UCanvasPanel;
class UHorizontalBox;
class UOverlay;
class UProgressBar;
class UTextBlock;

USTRUCT(BlueprintType)
struct FSkillCooldownData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UProgressBar> CooldownProgressBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTextBlock> CooldownTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle CooldownTimerHandle;

	FSkillCooldownData()
		: CooldownProgressBar(nullptr)
		, CooldownTextBlock(nullptr)
		, CooldownTime(0.0f)
	{
	}
};

UENUM(BlueprintType)
enum class ESkillRarity_Type : uint8
{
	NomalSkill, RareSkill, EpicSkill, LegendarySkill
};


UCLASS()
class GLADIATORSFANTASY_API UGFSkillCooldownWidgetSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSkillCooldownData CooldownData;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UProgressBar> SkillProgressBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> SkillTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTimerHandle CooldownTimerHandle;

	bool IsSkillCooldownActive;

	UFUNCTION(BlueprinTCallable)
	void UpdateSkillUI();

	UFUNCTION(BlueprinTCallable)
	void SetSkillCooldownActive(bool bIsActive);

	UFUNCTION(BlueprintCallable)
	void SetCooldownDataMap(FTimerHandle SkillTimer, float SkillCooldownTime);

};
