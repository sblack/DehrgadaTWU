// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "CommandDrivenController.h"

void ACommandDrivenController::ReceiveCommand(FCommand* command)
{
	Command = command;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Command Received!"));

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
		if (distSqr < Command->GetProximitySqr())
		{
			StopMovement();
			//Command = NULL;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Performing!"));
			bPerformingCommand = true;
			Command->Perform();
		}
	}
}

void ACommandDrivenController::ResolveCommand()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Vive la resolution!"));
	Command->Resolve();
	bLockCommand = true;
}

void ACommandDrivenController::CompleteCommand()
{
	bPerformingCommand = false;
	bLockCommand = false;

	Command = NULL;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Command Completed!"));
}
