// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FCommand.h"
#include "FCommandAttack.h"
#include "FCommandTalentActive.h"
#include "PCControllerMaster.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetTalents.h"
#include "CombatManagerCPP.h"
#include "CommandMenuCPP.h"

void UCommandMenuCPP::Prepare(FVector location)
{
	//UE_LOG(LogTemp, Log, TEXT("%d commands"), Commands.size());
	Commands.Empty();
	Commands.Add(new FCommand(location));
	if (ActiveCharacter == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("ActiveCharacter Missing"));
	else
	{
		for (int i = 0; i < ActiveCharacter->Talents->ActiveTalents.Num(); i++)
		{
			Commands.Add(new FCommandTalentActive(ActiveCharacter->Talents->ActiveTalents[i], location));
		}
	}
	
	SetupMenu();
}

void UCommandMenuCPP::Prepare(ITargetable target)
{
	Commands.Empty();
	Commands.Add(new FCommand(target));
	Commands.Add(new FCommandAttack(target));
	if (ActiveCharacter == nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("ActiveCharacter Missing"));
	else
	{
		for (int i = 0; i < ActiveCharacter->Talents->ActiveTalents.Num(); i++)
		{
			Commands.Add(new FCommandTalentActive(ActiveCharacter->Talents->ActiveTalents[i], target));
		}
	}
	SetupMenu();
}

void UCommandMenuCPP::SetupMenu()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetupMenu"));

	for (int i = 0; i < Commands.Num(); i++)
	{
		AddButton(Commands[i]->Name, i);
	}
	AddButton(FText::FromString("Cancel"), Commands.Num());
	if (UCombatManagerBFL::GetIsTurnBasedCombat())
	{
		AddButton(FText::FromString("End Turn"), -1);
	}

	Reposition(Commands.Num());
}

void UCommandMenuCPP::Select(int32 index)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::FromInt(index));

	Close();

	if (index == -1)
	{
		APCControllerMaster::Instance->EndTurn();
		return;
	}

	if (index < Commands.Num())
		APCControllerMaster::Instance->ReceiveCommandFromGUI(Commands[index]);
}