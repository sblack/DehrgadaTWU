// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"
#include "CombatEffectDamage.h"
#include "CombatEffect.h"

//combat effects are tried and applied until one fails. If you don't want that to happen, set NoDefense to true.
void UCombatEffect::ApplyEffects(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects, class ADehrgadaTWUCharacter* user, FVector location)
{
	for (int i = 0; i < effects.Num(); i++)
	{
		if (effects[i]->AttackRoll(target, user))
		{
			effects[i]->Apply(target, user, location);
		}
		else
		{
			//if the effect is damage AND does half on miss, do half for it and all following damages that are halved on miss
			//after that, or otherwise, don't try any more effects.
			if (effects[i]->IsA<UCombatEffectDamage>())
			{
				UCombatEffectDamage* damage = Cast<UCombatEffectDamage>(effects[i]);
				if (damage->bHalfOnMiss)
				{
					damage->Apply_MA(target, user, .5f, 0);
					for (int j = i + 1; j < effects.Num(); j++)
					{
						if (effects[i]->IsA<UCombatEffectDamage>())
						{
							damage = Cast<UCombatEffectDamage>(effects[i]);
							if (damage->bHalfOnMiss)
							{
								damage->Apply_MA(target, user, .5f, 0);
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}

			}
			break;
		}
	}
}

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
