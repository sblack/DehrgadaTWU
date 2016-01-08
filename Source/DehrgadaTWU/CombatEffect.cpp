// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"
#include "CombatEffectDamage.h"
#include "CombatEffect.h"

void UCombatEffect::ApplyEffects(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < effects.Num(); i++)
	{
		effects[i]->Apply(target, user, location);
	}
}

void UCombatEffect::ApplyEffectsHalf(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < effects.Num(); i++)
	{
		effects[i]->ApplyHalf(target, user, location);
	}
}

void UCombatEffect::RemoveEffects(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects)
{
	for (int i = 0; i < effects.Num(); i++)
	{
		effects[i]->Remove(target);
	}
}