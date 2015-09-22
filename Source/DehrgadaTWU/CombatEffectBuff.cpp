// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatEffectBuff.h"

void UCombatEffectBuff::Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < Buffs.Num(); i++)
	{
		target->ApplyBuff(Buffs[i]);
	}
}


