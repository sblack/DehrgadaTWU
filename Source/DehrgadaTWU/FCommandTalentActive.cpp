// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "PCControllerSlave.h"
#include "TalentManagerCPP.h"
#include "FCommandTalentActive.h"

FCommandTalentActive::FCommandTalentActive() : FCommand()
{
	Name = FText::FromString("Talent");
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent) : FCommand()
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->Range;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, ITargetable target) : FCommand(target)
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->Range;
	if (Proximity < 150) Proximity = 150;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, FVector location) : FCommand(location)
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->Range;
	if (Proximity < 10) Proximity = 10;
}

FCommandTalentActive::~FCommandTalentActive()
{
}

void FCommandTalentActive::Perform()
{
	Performer->GetDehrgadaTWUCharacter()->bCasting = true;
}

void FCommandTalentActive::Resolve()
{
	if (Target && Talent->bCanTargetActor)
	{
		ATalentManagerCPP::Instance->Use_Target(Talent, Performer->GetDehrgadaTWUCharacter(), Target);
	}
	else
	{
		ATalentManagerCPP::Instance->Use_Location(Talent, Performer->GetDehrgadaTWUCharacter(), TargetLocation);
	}
}