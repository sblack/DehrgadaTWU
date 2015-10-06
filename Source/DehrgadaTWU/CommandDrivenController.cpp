// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "CombatManagerCPP.h"
#include "CommandDrivenController.h"

float ACommandDrivenController::RecalculateInitiative()
{
	Initiative = GetDehrgadaTWUCharacter()->Stats->AttributesTotal[(int)EAttributes::Dexterity] + FMath::FRandRange(0, 20);
	return Initiative;
}

void ACommandDrivenController::SetIsMyTurn(bool isMyTurn)
{
	if (bIsMyTurn == isMyTurn)
	{
		return;
	}
	if (isMyTurn)
	{

	}
	else
	{
		if (!bPerformingCommand)
		{
			CancelCommand();
		}
		else
		{
			ACombatManagerCPP::Instance->IncrementPendingTBCounter();
		}
	}
	bIsMyTurn = isMyTurn;
}

void ACommandDrivenController::StartTurn()
{
	bIsMyTurn = true;
	OldLocation = GetPawn()->GetActorLocation();
	GetDehrgadaTWUCharacter()->Stats->UpdateAPForNewTurn();
}

void ACommandDrivenController::EndTurn()
{
	bIsMyTurn = false;
	CancelCommand();
	ACombatManagerCPP::Instance->AdvanceInitiative();
}

void ACommandDrivenController::ReceiveCommand(FCommand* command)
{
	if (!bIsMyTurn)
	{
		return;
	}

	if (bLockCommand)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Command Lock. New Command Ignored."));
		UE_LOG(LogTemp, Log, TEXT("Ignore %s %d"), *command->Name.ToString(), command->GetID());
		return;
	}

	if (!command->CanUse(GetDehrgadaTWUCharacter()))
	{
		UE_LOG(LogTemp, Log, TEXT("Can't use %s %d (RC)"), *command->Name.ToString(), command->GetID());
		return;
	}

	CancelCommand();
	Command = command;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Command Received!"));
	UE_LOG(LogTemp, Log, TEXT("Receive %s %d"), *Command->Name.ToString(), Command->GetID());

	LoadCommand();
}

void ACommandDrivenController::LoadCommand()
{
	if (Command)
	{
		Command->Performer = this;
		if (Command->GetTarget())
		{
			SetNewMoveDestination(Command->GetTarget());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Pawn!"));
		}
		else
		{
			SetNewMoveDestination(Command->GetTargetLocation());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Location!"));
		}
	}
}

void ACommandDrivenController::SetNewMoveDestination(const FVector destLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(destLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, destLocation);
		}
	}
}

void ACommandDrivenController::SetNewMoveDestination(ITargetable target)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(target->Location(), Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToActor(this, target->AsActor());
		}
	}
}

void ACommandDrivenController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Yes, this works"));
}

void ACommandDrivenController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Command)
	{
		float distSqr = FVector::DistSquared(GetDehrgadaTWUCharacter()->GetFeetLocation(), Command->GetTargetLocation());
		if (distSqr < Command->GetProximitySqr() && !bPerformingCommand)
		{
			StopMovement();
			//Command = NULL;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Performing!"));
			if (Command->CanUse(GetDehrgadaTWUCharacter()))
			{
				bPerformingCommand = true;
				Command->Perform();
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Can't use %s %d (T)"), *Command->Name.ToString(), Command->GetID());
				CancelCommand();
			}
		}

		if (UCombatManagerBFL::GetIsTurnBasedCombat() && bIsMyTurn)
		{
			float traveled = (GetPawn()->GetActorLocation() - OldLocation).Size();
			GetDehrgadaTWUCharacter()->Stats->APCurrent -= (traveled / 100.f);
			OldLocation = GetPawn()->GetActorLocation();
			if (GetDehrgadaTWUCharacter()->Stats->APCurrent <= 0)
			{
				UE_LOG(LogTemp, Log, TEXT("No AP Left"));
				EndTurn();
			}
		}
	}
}

void ACommandDrivenController::ResolveCommand()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Vive la resolution!"));
	UE_LOG(LogTemp, Log, TEXT("Resolve %s %d"), *Command->Name.ToString(), Command->GetID());
	Command->Resolve();
	bLockCommand = true;
	if (UCombatManagerBFL::GetIsTurnBasedCombat())
	{
		GetDehrgadaTWUCharacter()->Stats->APCurrent -= Command->BaseAP;
	}
}

void ACommandDrivenController::CompleteCommand()
{
	bPerformingCommand = false;
	bLockCommand = false;

	UE_LOG(LogTemp, Log, TEXT("Complete %s %d"), *Command->Name.ToString(), Command->GetID());
	Command = NULL;
	if (UCombatManagerBFL::GetRTTBState() == ERTTBState::PendingTB)
	{
		ACombatManagerCPP::Instance->DecrementPendingTBCounter();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Command Completed!"));
}

void ACommandDrivenController::CancelCommand()
{
	bPerformingCommand = false;
	GetDehrgadaTWUCharacter()->bCancel = true;
	StopMovement();
	if (Command != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Cancel %s %d"), *Command->Name.ToString(), Command->GetID());
		Command = NULL;
	}
}
