// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "CombatEffect.h"
#include "AttackRoll.h"

bool UAttackRoll::RollAttack(TScriptInterface<ITargetableInterface> target, ADehrgadaTWUCharacter* user)
{
	if (bAutoHit)
		return true;
	//TODO
	return true;
}

bool UAttackRoll::RollAttack_NoUser(TScriptInterface<ITargetableInterface> target, float attackBonus)
{
	if (bAutoHit)
		return true;
	//TODO
	return true;
}

void UAttackRoll::RollAttacks(TScriptInterface<ITargetableInterface> target, ADehrgadaTWUCharacter* user, TArray<UAttackRoll*> attacks, FVector location)
{
	for (int i = 0; i < attacks.Num(); i++)
	{
		if (attacks[i]->RollAttack(target, user))
		{
			UCombatEffect::ApplyEffects(target, attacks[i]->Effects, user, location);
		}
		else
		{
			if(attacks[i]->bHalfOnMiss)
				UCombatEffect::ApplyEffectsHalf(target, attacks[i]->Effects, user, location);

			break;
		}
	}
}

void UAttackRoll::RollAttacks_NoUser(TScriptInterface<ITargetableInterface> target, float attackBonus, TArray<UAttackRoll*> attacks, FVector location)
{
	for (int i = 0; i < attacks.Num(); i++)
	{
		if (attacks[i]->RollAttack_NoUser(target, attackBonus))
		{
			UCombatEffect::ApplyEffects(target, attacks[i]->Effects, nullptr, location);
		}
		else
		{
			if (attacks[i]->bHalfOnMiss)
				UCombatEffect::ApplyEffectsHalf(target, attacks[i]->Effects, nullptr, location);

			break;
		}
	}
}

