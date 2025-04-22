// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GFSkillCooldownWidget.h"
#include "Skill/GFSkillCooldownWidgetSlot.h"

TArray<UGFSkillCooldownWidgetSlot*> UGFSkillCooldownWidget::GetCooldownSlots() const
{
	return CooldownSlots;
}

void UGFSkillCooldownWidget::AddCooldownSlots(UGFSkillCooldownWidgetSlot* CooldownSlot)
{
	CooldownSlots.Add(CooldownSlot);
}

void UGFSkillCooldownWidget::ActivateSkills()
{
	InitAllSkillActivate(false);
	for (int i = 0; i < CooldownSlots.Num(); ++i)
	{
		if (CooldownSlots[i])
		{
			if ((int)WeaponRarityType >= i)
			{
				CooldownSlots[i]->SetSkillCooldownActive(true);
			}
		}
	}
}

void UGFSkillCooldownWidget::InitAllSkillActivate(bool bIsActivate)
{
	for (UGFSkillCooldownWidgetSlot* CooldownSlot : CooldownSlots)
	{
		if (CooldownSlot)
		{
			CooldownSlot->SetSkillCooldownActive(bIsActivate);
		}
	}
}

void UGFSkillCooldownWidget::SetSkillSlotRarity()
{
	for (int i = 0; i < CooldownSlots.Num(); ++i)
	{
		if (CooldownSlots[i])
		{
			CooldownSlots[i]->SetSlotRarity(i);
		}
	}
}
