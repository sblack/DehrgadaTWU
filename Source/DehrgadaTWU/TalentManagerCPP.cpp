// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "TalentManagerCPP.h"

ATalentManagerCPP* ATalentManagerCPP::Instance;

void ATalentManagerCPP::SetInstance()
{
	Instance = this;
}


