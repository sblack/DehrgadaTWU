// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatEffect.h"
#include "Attack.h"

UAttack::UAttack()
{
	/*Effects.Add(NewObject<class UCombatEffectDamage>((UObject*)GetTransientPackage()));*/
	//Effects.Add(NewObject<class UCombatEffectDamage>(GetOuter(), "Fred"));
	PrimaryEffect = NewObject<class UCombatEffectDamage>(GetOuter(), "Fred");
}


