// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "DehrgadaTWUCharacter.h"
#include "RollCalculatorCPP.h"
#include "FCommandAttack.h"

FCommandAttack::FCommandAttack(APawn* pawn) : FCommand(pawn)
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
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Miss.");
	}
}