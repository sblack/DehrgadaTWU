// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatManagerCPP.h"

ACombatManagerCPP* ACombatManagerCPP::Instance;

void ACombatManagerCPP::SetInstance(ACombatManagerCPP* instance)
{
	Instance = instance;
}

