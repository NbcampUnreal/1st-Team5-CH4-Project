// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GFSkillCooldownWidgetSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/Progressbar.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"


void UGFSkillCooldownWidgetSlot::NativeConstruct()
{
	Super::NativeConstruct();

	IsSkillCooldownActive = false;
	SkillProgressBar->SetPercent(0);
}

void UGFSkillCooldownWidgetSlot::UpdateSkillUI()
{
	if (CooldownTimerHandle.IsValid() == false || IsSkillCooldownActive == false)
	{
		return;
	}
	float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimerHandle);

	SkillProgressBar->SetPercent(RemainingTime / CooldownTime);
	SkillTextBlock->SetVisibility(ESlateVisibility::Visible);

	SkillTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), RemainingTime)));

	if (RemainingTime <= 0)
	{
		SkillTextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGFSkillCooldownWidgetSlot::SetSkillCooldownActive(bool bIsActive)
{
	IsSkillCooldownActive = bIsActive;
	SkillTextBlock->SetVisibility(ESlateVisibility::Hidden);
	SkillProgressBar->SetPercent(0);
	if (bIsActive)
	{
		SkillProgressBar->WidgetStyle.BackgroundImage.TintColor = FSlateColor(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
	else
	{
		SkillProgressBar->WidgetStyle.BackgroundImage.TintColor = FSlateColor(FLinearColor(0.1f, 0.1f, 0.1f, 1.0f));
		CooldownTimerHandle = FTimerHandle();
	}
	
}

void UGFSkillCooldownWidgetSlot::SetCooldownDataMap(FTimerHandle SkillTimer, float SkillCooldownTime)
{
	CooldownTimerHandle = SkillTimer;
	CooldownTime = SkillCooldownTime;
}
