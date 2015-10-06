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

void ACombatManagerCPP::SetInCombat(bool inCombat)
{
	if (inCombat == bInCombat) return;

	bInCombat = inCombat;
	if (bInCombat)
	{
		//BEGIN COMBAT
		switch (RTTBState)
		{
		case ERTTBState::RealTime:
			return;
		case ERTTBState::TurnBased:
			RTTBState = ERTTBState::PendingTB;
			PrepareForTurnBased();
			return;
		default:
			return;
		}
	}
	else
	{
		//END COMBAT

		InitiativeQueue.Empty();

		switch (RTTBState)
		{
		case ERTTBState::RealTime:
			return;
		case ERTTBState::PendingTB:
			RTTBState = ERTTBState::TurnBased;
			return;
		case ERTTBState::TurnBased:
			EndTurnBased();
			return;
		case ERTTBState::PendingRT:
			RTTBState = ERTTBState::RealTime;
			EndTurnBased();
			return;
		default:
			return;
		}
	}
}

void ACombatManagerCPP::ToggleRTTB()
{
	if (bInCombat)
	{
		switch (RTTBState)
		{
		case ERTTBState::RealTime:
			RTTBState = ERTTBState::PendingTB;
			PrepareForTurnBased();
			return;
		case ERTTBState::PendingTB:
			RTTBState = ERTTBState::RealTime;
			EndTurnBased();
			return;
		case ERTTBState::TurnBased:
			RTTBState = ERTTBState::PendingRT;
			return;
		case ERTTBState::PendingRT:
			RTTBState = ERTTBState::TurnBased;
			return;
		default:
			return;
		}
	}
	else
	{
		if (RTTBState == ERTTBState::RealTime || RTTBState == ERTTBState::PendingRT)
		{
			RTTBState = ERTTBState::TurnBased;
		}
		else
		{
			RTTBState = ERTTBState::RealTime;
		}
	}
}

void ACombatManagerCPP::PrepareForTurnBased()
{
	if (InitiativeQueue.Num() == 0)
	{
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
	}
	if (PendingTBCounter == 0)
	{
		RTTBState = ERTTBState::TurnBased;
		BeginTurnBased();
	}
}

void ACombatManagerCPP::BeginTurnBased()
{
	AWorldTimer::Instance->bIsRunning = false;
	UE_LOG(LogTemp, Log, TEXT("BeginTurnBased"));
	CurrentInitiative = -1;
	AdvanceInitiative();
}

void ACombatManagerCPP::EndTurnBased()
{
	AWorldTimer::Instance->bIsRunning = true;
	UE_LOG(LogTemp, Log, TEXT("EndTurnBased"));
	for (int i = 0; i < InitiativeQueue.Num(); i++)
	{
		InitiativeQueue[i]->SetIsMyTurn(true);
	}
}

void ACombatManagerCPP::AdvanceInitiative()
{
	CurrentInitiative++;
	if (CurrentInitiative >= InitiativeQueue.Num())
	{
		CurrentInitiative = 0;
		//TODO: new round logic
		AWorldTimer::Instance->AdvanceOneTurn();
		if (RTTBState == ERTTBState::PendingRT)
		{
			RTTBState = ERTTBState::RealTime;
			EndTurnBased();
			return;
		}
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

void ACombatManagerCPP::DecrementPendingTBCounter()
{
	if (--PendingTBCounter < 1)
	{
		RTTBState = ERTTBState::TurnBased;
		BeginTurnBased();
	}
}