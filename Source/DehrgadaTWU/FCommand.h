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
	static int Count;

	int ID;
	
	/** distance at which Performer should stop moving and act */
	float Proximity;
public:
	class ACommandDrivenController* Performer;

	FText Name;

	int GetID() const { return ID; }

	UPROPERTY(BlueprintReadOnly)
	FVector TargetLocation;

	UPROPERTY(BlueprintReadOnly)
		TScriptInterface<ITargetableInterface> Target;

	UPROPERTY(BlueprintReadOnly)
		float BaseAP;

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

	virtual bool CanUse(class ADehrgadaTWUCharacter* user);

	virtual void Perform();

	virtual void Resolve();
};
