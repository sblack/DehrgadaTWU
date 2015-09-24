// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "FCommand.h"
#include "CommandDrivenController.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API ACommandDrivenController : public AAIController
{
	GENERATED_BODY()
protected:
	FCommand* Command;

	void LoadCommand();

public:

	class ADehrgadaTWUCharacter* GetDehrgadaTWUCharacter() { return (ADehrgadaTWUCharacter*)GetCharacter(); }

	void ReceiveCommand(FCommand* command);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector destLocation);

	/** Navigate player to the given target. */
	void SetNewMoveDestination(ITargetable target);

	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, Category = "Command")
		bool bPerformingCommand;

	UPROPERTY(BlueprintReadWrite, Category = "Command")
		bool bLockCommand;

	UFUNCTION(BlueprintCallable, Category = "Command")
		void ResolveCommand();

	UFUNCTION(BlueprintCallable, Category = "Command")
		void CompleteCommand();
};
