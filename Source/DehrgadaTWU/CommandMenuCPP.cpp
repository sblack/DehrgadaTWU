// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include <vector>
#include "FCommand.h"
#include "FCommandAttack.h"
#include "PCControllerMaster.h"
#include "CommandMenuCPP.h"

void UCommandMenuCPP::Prepare(FVector location)
{
	//UE_LOG(LogTemp, Log, TEXT("%d commands"), Commands.size());
	Commands.clear();
	Commands.insert(Commands.end(), new FCommand(location));
	
	SetupMenu();
}

void UCommandMenuCPP::Prepare(AActor* target)
{
	Commands.clear();
	APawn* targetPawn = (APawn*)target;
	if (targetPawn != NULL)
	{
		Commands.insert(Commands.end(), new FCommand(targetPawn));
		Commands.insert(Commands.end(), new FCommandAttack(targetPawn));
	}
	
	SetupMenu();
}

void UCommandMenuCPP::SetupMenu()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SetupMenu"));

	for (int i = 0; i < Commands.size(); i++)
	{
		AddButton(Commands[i]->Name, i);
	}
	AddButton("Cancel", Commands.size());

	Reposition(Commands.size());
}

void UCommandMenuCPP::Select(int32 index)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::FromInt(index));

	Close();

	if (index < Commands.size())
		((APCControllerMaster*)(GetWorld()->GetFirstPlayerController()))->ReceiveCommandFromGUI(Commands[index]);
}