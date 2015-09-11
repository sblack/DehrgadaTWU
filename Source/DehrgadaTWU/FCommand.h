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
		TScriptInterface<ITargetableInterface> Target;

	ITargetable GetTarget() const { return Target; }

	FVector	GetTargetLocation() const
	{
		if (Target) return Target->Location();
		return TargetLocation;
	}

	float GetProximitySqr() { return Proximity * Proximity; }

	FCommand();

	FCommand(FVector location);

	FCommand(ITargetable target);

	~FCommand();

	virtual void Perform();

	virtual void Resolve();
};
