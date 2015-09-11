// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CommandsBFL.h"



FCommand UCommandsBFL::MoveTo(FVector location)
{
	return FCommand(location);
}

FCommand UCommandsBFL::Approach(TScriptInterface<ITargetableInterface> target)
{
	return FCommand(target);
}

FCommandAttack UCommandsBFL::Attack(TScriptInterface<ITargetableInterface> target)
{
	return FCommandAttack(target);
}
