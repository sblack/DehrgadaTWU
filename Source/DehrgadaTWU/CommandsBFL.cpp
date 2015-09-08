// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CommandsBFL.h"



FCommand UCommandsBFL::MoveTo(FVector location)
{
	return FCommand(location);
}

FCommand UCommandsBFL::Approach(APawn* pawn)
{
	return FCommand(pawn);
}

FCommandAttack UCommandsBFL::Attack(APawn* pawn)
{
	return FCommandAttack(pawn);
}
