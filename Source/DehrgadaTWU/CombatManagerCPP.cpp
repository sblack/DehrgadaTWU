// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CommandDrivenController.h"
#include "PCControllerMaster.h"
#include "PCControllerSlave.h"
#include "CameraPawn.h"
#include "CombatManagerCPP.h"

ACombatManagerCPP* ACombatManagerCPP::Instance;

void ACombatManagerCPP::SetInstance()
{
	Instance = this;
}

void ACombatManagerCPP::BeginTurnBased()
{
	bIsTurnBased = true;
	bInCombat = true;
	UE_LOG(LogTemp, Log, TEXT("BeginTurnBased"));
	InitiativeQueue.Empty();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UInitiativeObjectInterface::StaticClass(), temp);
	for (int i = 0; i < temp.Num(); i++)
	{
		IInitiativeObject ini = IInitiativeObjectInterface::InitiativeObject(temp[i]);
		ini->SetIsMyTurn(false);
		ini->RecalculateInitiative();
		InitiativeQueue.Add(ini);
	}
	UE_LOG(LogTemp, Log, TEXT("Found %d"), temp.Num());
	InitiativeQueue.Sort([](const IInitiativeObject A, const IInitiativeObject B) { return A->GetInitiative() > B->GetInitiative(); });
	for (int i = 0; i < InitiativeQueue.Num(); i++)
	{
		UE_LOG(LogTemp, Log, TEXT("%f %s"), InitiativeQueue[i]->GetInitiative(), *InitiativeQueue[i]->_getUObject()->GetName());
	}
	CurrentInitiative = -1;
	AdvanceInitiative();
}

void ACombatManagerCPP::AdvanceInitiative()
{
	CurrentInitiative++;
	if (CurrentInitiative >= InitiativeQueue.Num())
	{
		CurrentInitiative = 0;
		//TODO: new round logic
	}
	InitiativeQueue[CurrentInitiative]->StartTurn();
	ACommandDrivenController* cdc = Cast<ACommandDrivenController>(InitiativeQueue[CurrentInitiative]->_getUObject());
	if (cdc)
	{
		ACameraPawn::Instance->AttachCamera(cdc->GetDehrgadaTWUCharacter());
		if (cdc->IsA<APCControllerSlave>())
		{
			APCControllerMaster::Instance->SwitchToSlave(Cast<APCControllerSlave>(cdc)->slaveIndex);
			ACameraPawn::Instance->bLocked = false;
		}
		else
		{
			ACameraPawn::Instance->bLocked = true;
		}
	}
}