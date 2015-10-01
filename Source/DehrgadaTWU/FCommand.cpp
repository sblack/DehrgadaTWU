// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CommandDrivenController.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "CombatManagerCPP.h"
#include "FCommand.h"

int FCommand::Count = 0;

FCommand::FCommand()
{
	Name = FText::FromString("Umm...");
	ID = Count++;
	BaseAP = 0;
}

FCommand::FCommand(FVector location)
{
	TargetLocation = location;
	Target = TScriptInterface<ITargetableInterface>();
	Proximity = 50;
	Name = FText::FromString("Move");
	ID = Count++;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, location.ToString());
	BaseAP = 0;
}

FCommand::FCommand(ITargetable target)
{
	Target = target;
	Proximity = 150;
	Name = FText::FromString("Approach");
	ID = Count++;
	BaseAP = 0;
}

FCommand::~FCommand()
{
}

bool FCommand::CanUse(ADehrgadaTWUCharacter* user)
{
	if (UCombatManagerBFL::GetIsTurnBasedCombat())
	{
		if (user->Stats->APCurrent < BaseAP)
		{
			return false;
		}
	}

	return true;
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