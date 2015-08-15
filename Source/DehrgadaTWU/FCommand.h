// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DEHRGADATWU_API FCommand
{
protected:
	FVector TargetLocation;
	class APawn* TargetPawn;
	/** distance at which Performer should stop moving and act */
	float Proximity;
public:
	class APCControllerSlave* Performer;

	class APawn* GetTargetPawn() const { return TargetPawn; }

	FVector	GetTargetLocation() const
	{
		if (TargetPawn) return TargetPawn->GetActorLocation();
		return TargetLocation;
	}

	float GetProximitySqr() { return Proximity * Proximity; }

	FCommand(FVector location);

	FCommand(APawn* pawn);

	~FCommand();

	virtual void Perform();

	virtual void Resolve();
};
