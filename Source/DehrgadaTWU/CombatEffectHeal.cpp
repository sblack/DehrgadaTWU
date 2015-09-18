// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatEffectHeal.h"

void UCombatEffectHeal::Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < Heal.Num(); i++)
	{
		target->ApplyHeal(Heal[i]);
	}
}


