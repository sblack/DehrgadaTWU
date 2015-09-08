// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FCommand.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEHRGADATWU_API FCommand
{
	GENERATED_USTRUCT_BODY()
protected:
	
	/** distance at which Performer should stop moving and act */
	float Proximity;
public:
	class APCControllerSlave* Performer;

	//probably want to change this to FText eventually
	FString Name;

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation;

	UPROPERTY(BlueprintReadOnly)
	class APawn* TargetPawn;

	class APawn* GetTargetPawn() const { return TargetPawn; }

	FVector	GetTargetLocation() const
	{
		if (TargetPawn) return TargetPawn->GetActorLocation();
		return TargetLocation;
	}

	float GetProximitySqr() { return Proximity * Proximity; }

	FCommand();

	FCommand(FVector location);

	FCommand(APawn* pawn);

	~FCommand();

	virtual void Perform();

	virtual void Resolve();
};
