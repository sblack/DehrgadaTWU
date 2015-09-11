// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "RollCalculatorCPP.h"
#include "DamageData.h"
#include "FCommandAttack.h"

FCommandAttack::FCommandAttack() : FCommand()
{
	Name = "Attack";
}

FCommandAttack::FCommandAttack(ITargetable target) : FCommand(target)
{
	Name = "Attack";
}

FCommandAttack::~FCommandAttack()
{
}

void FCommandAttack::Perform()
{
	Performer->GetDehrgadaTWUCharacter()->bAttacking = true;
}

void FCommandAttack::Resolve()
{
	bool result;
	URollCalculatorCPP::Instance->RollAttack(result);
	if (result)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Hit!");
		UDamageData* damage = UDamageData::NewDamage(EDamage::Slashing, EVitals::Health, 1, 5);
		Target->ApplyDamage(damage, 1.f, 0);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Miss.");
	}
}