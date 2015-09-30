// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "InitiativeObjectInterface.h"
#include "FCommand.h"
#include "FCommandAttack.h"
#include "CommandDrivenController.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API ACommandDrivenController : public AAIController, public IInitiativeObjectInterface
{
	GENERATED_BODY()
protected:
	FCommand* Command;

	void LoadCommand();

	float Initiative;

	FVector OldLocation;

public:
	UFUNCTION(BlueprintPure, Category = "Command")
		bool HasCommand() const { return (Command != nullptr); }

	class ADehrgadaTWUCharacter* GetDehrgadaTWUCharacter() { return (ADehrgadaTWUCharacter*)GetCharacter(); }

	void ReceiveCommand(FCommand* command);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector destLocation);

	/** Navigate player to the given target. */
	void SetNewMoveDestination(ITargetable target);

	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		float RecalculateInitiative() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		float GetInitiative() const override { return Initiative; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void StartTurn() override;

	void EndTurn();

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void SetIsMyTurn(bool isMyTurn) override;

	UPROPERTY(BlueprintReadWrite, Category = "Command")
		bool bPerformingCommand;

	UPROPERTY(BlueprintReadWrite, Category = "Command")
		bool bLockCommand;

	UFUNCTION(BlueprintCallable, Category = "Command")
		void ResolveCommand();

	UFUNCTION(BlueprintCallable, Category = "Command")
		void CompleteCommand();

	UFUNCTION(BlueprintCallable, Category = "Command")
		void CancelCommand();

	UFUNCTION(BlueprintCallable, Category = "Command")
		void Command_MoveTo(FVector location) { ReceiveCommand(new FCommand(location)); }

	UFUNCTION(BlueprintCallable, Category = "Command")
		void Command_Approach(TScriptInterface<ITargetableInterface> target) { ReceiveCommand(new FCommand(target)); }

	UFUNCTION(BlueprintCallable, Category = "Command")
		void Command_Attack(TScriptInterface<ITargetableInterface> target) { ReceiveCommand(new FCommandAttack(target)); }
};
