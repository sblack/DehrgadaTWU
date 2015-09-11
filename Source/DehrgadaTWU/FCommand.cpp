// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "Engine.h"
#include "FCommand.h"

FCommand::FCommand()
{
	Name = "Umm...";
}

FCommand::FCommand(FVector location)
{
	TargetLocation = location;
	Target = TScriptInterface<ITargetableInterface>();
	Proximity = 10;
	Name = "Move";
}

FCommand::FCommand(ITargetable target)
{
	Target = target;
	Proximity = 150;
	Name = "Approach";
}

FCommand::~FCommand()
{
}

void FCommand::Perform()
{
	//do nothing.
	Performer->CompleteCommand();
}

void FCommand::Resolve()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("resolution!"));
}