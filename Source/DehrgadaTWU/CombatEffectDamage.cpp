// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatEffectDamage.h"

void UCombatEffectDamage::Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < Damage.Num(); i++)
	{
		target->ApplyDamage(Damage[i],1.f,0);
	}
}

void UCombatEffectDamage::Apply_MA(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, float mult, int32 add)
{
	for (int i = 0; i < Damage.Num(); i++)
	{
		target->ApplyDamage(Damage[i], mult, add);
	}
}

