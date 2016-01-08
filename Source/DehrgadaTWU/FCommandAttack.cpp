// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "RollCalculatorCPP.h"
#include "DamageData.h"
#include "ItemWeapon.h"
#include "Attack.h"
#include "CombatEffect.h"
#include "AttackRoll.h"
#include "FCommandAttack.h"

FCommandAttack::FCommandAttack() : FCommand()
{
	Name = FText::FromString("Attack");
	BaseAP = 4;
}

FCommandAttack::FCommandAttack(ITargetable target) : FCommand(target)
{
	Name = FText::FromString("Attack");
	BaseAP = 4;
}

FCommandAttack::FCommandAttack(ITargetable target, UItemWeapon* weapon, UAttack* attack) : FCommand(target)
{
	if (weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CommandAttack: Weapon is NULL."));
		return;
	}
	if (weapon->Attacks.Num() == 0 || weapon->Attacks[0] == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CommandAttack: Weapon %s has no Attack[0]."), *weapon->Name.ToString());
		return;
	}

	Weapon = weapon;
	//may want to make a copy of the attack instead
	if (attack != nullptr)
		Attack = attack;
	else
		Attack = weapon->Attacks[0];

	Name = Attack->Name;
	BaseAP = Attack->BaseAP;
	Proximity = Attack->Range;
}

FCommandAttack::~FCommandAttack()
{
}

bool FCommandAttack::CanUse(ADehrgadaTWUCharacter* user)
{
	return FCommand::CanUse(user);
}

void FCommandAttack::Perform()
{
	Performer->GetDehrgadaTWUCharacter()->bAttacking = true;
}

void FCommandAttack::Resolve()
{
	UE_LOG(LogTemp, Log, TEXT("-----------"));
	bool result = true;

	if (Attack->bIsMelee)
	{
		ARollCalculatorCPP::Instance->MeleeAttack(Target, Performer->GetDehrgadaTWUCharacter(), EDefenses::Deflection, result);
	}
	//TODO switch on attack types (melee, ranged, weave)

	if (result)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Hit!");
		UE_LOG(LogTemp, Log, TEXT("Hit"));
		/*UDamageData* damage = UDamageData::NewDamage(EDamage::Slashing, EVitals::Health, 1, 5);
		Target->ApplyDamage(damage, 1.f, 0);*/
		UCombatEffect::ApplyEffects(Target, Weapon->BonusEffects, Performer->GetDehrgadaTWUCharacter(), Performer->GetDehrgadaTWUCharacter()->GetActorLocation());
		UCombatEffect::ApplyEffects(Target, Attack->Effects, Performer->GetDehrgadaTWUCharacter(), Performer->GetDehrgadaTWUCharacter()->GetActorLocation());
		UAttackRoll::RollAttacks(Target, Performer->GetDehrgadaTWUCharacter(), Attack->SubsequentRolls, Performer->GetDehrgadaTWUCharacter()->GetActorLocation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Miss.");
		UE_LOG(LogTemp, Log, TEXT("Miss"));
	}
}