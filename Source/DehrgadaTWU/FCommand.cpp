// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CommandDrivenController.h"
#include "FCommand.h"

FCommand::FCommand()
{
	Name = FText::FromString("Umm...");
}

FCommand::FCommand(FVector location)
{
	TargetLocation = location;
	Target = TScriptInterface<ITargetableInterface>();
	Proximity = 50;
	Name = FText::FromString("Move");
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, location.ToString());
}

FCommand::FCommand(ITargetable target)
{
	Target = target;
	Proximity = 150;
	Name = FText::FromString("Approach");
}

FCommand::~FCommand()
{
}

void FCommand::Perform()
{
	//do nothing.
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Perform!"));
	Performer->CompleteCommand();
}

void FCommand::Resolve()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("resolution!"));
}