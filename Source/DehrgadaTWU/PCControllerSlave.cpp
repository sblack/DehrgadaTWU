// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FCommand.h"
#include "Engine.h"
#include "PCControllerSlave.h"

void APCControllerSlave::ReceiveCommand(FCommand* command)
{
	Command = command;

	LoadCommand();
}

void APCControllerSlave::LoadCommand()
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

void APCControllerSlave::SetNewMoveDestination(const FVector destLocation)
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

void APCControllerSlave::SetNewMoveDestination(ITargetable target)
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

void APCControllerSlave::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Yes, this works"));
}

void APCControllerSlave::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (Command)
	{
		float distSqr = FVector::DistSquared(GetPawn()->GetActorLocation(), Command->GetTargetLocation());
		if (distSqr < Command->GetProximitySqr())
		{
			StopMovement();
			//Command = NULL;
			Command->Perform();
			bPerformingCommand = true;
		}
	}
}

void APCControllerSlave::ResolveCommand()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Vive la resolution!"));
	Command->Resolve();
	bLockCommand = true;
}

void APCControllerSlave::CompleteCommand()
{
	bPerformingCommand = false;
	bLockCommand = false;

	Command = NULL;
}