// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "DehrgadaTWUCharacter.h"
#include "FCommandAttack.h"

FCommandAttack::FCommandAttack(APawn* pawn) : FCommand(pawn)
{

}

FCommandAttack::~FCommandAttack()
{
}

void FCommandAttack::Perform()
{
	Performer->GetDehrgadaTWUCharacter()->bAttacking = true;
}