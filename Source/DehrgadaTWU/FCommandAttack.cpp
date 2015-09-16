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
	Name = FText::FromString("Attack");
}

FCommandAttack::FCommandAttack(ITargetable target) : FCommand(target)
{
	Name = FText::FromString("Attack");
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
	UE_LOG(LogTemp, Log, TEXT("-----------"));
	bool result = true;
	URollCalculatorCPP::Instance->MeleeAttack(Target, Performer->GetDehrgadaTWUCharacter(), EDefenses::Deflection, result);
	if (result)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Green, "Hit!");
		UE_LOG(LogTemp, Log, TEXT("Hit"));
		UDamageData* damage = UDamageData::NewDamage(EDamage::Slashing, EVitals::Health, 1, 5);
		Target->ApplyDamage(damage, 1.f, 0);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Miss.");
		UE_LOG(LogTemp, Log, TEXT("Miss"));
	}
}