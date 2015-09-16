// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FCommandTalentActive.h"

FCommandTalentActive::FCommandTalentActive() : FCommand()
{
	Name = FText::FromString("Talent");
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent) : FCommand()
{
	Name = talent->Name;
	Talent = talent;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, ITargetable target) : FCommand(target)
{
	Name = talent->Name;
	Talent = talent;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, FVector location) : FCommand(location)
{
	Name = talent->Name;
	Talent = talent;
}

FCommandTalentActive::~FCommandTalentActive()
{
}
