// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"
#include "CombatEffect.h"

bool UCombatEffectResistable::AttackRoll(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user)
{
	if (bNoDefense) return true;

	bool ret;
	if (bUseMeleeAttackRoll)
	{
		URollCalculatorCPP::Instance->MeleeAttack(target, user, Defense, ret);
	}
	else
	{
		URollCalculatorCPP::Instance->MagicAttack(target, user, Defense, ret);
	}

	return ret;
}

bool UCombatEffectResistable::AttackRoll_NoUser(TScriptInterface<ITargetableInterface> target, float attackMod)
{
	if (bNoDefense) return true;

	bool ret;
	URollCalculatorCPP::Instance->Attack_NoUser(target, attackMod, Defense, ret);
	return ret;
}
