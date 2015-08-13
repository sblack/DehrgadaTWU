// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "PCControllerSlave.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API APCControllerSlave : public AAIController
{
	GENERATED_BODY()

public:

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	int slaveIndex;

};
