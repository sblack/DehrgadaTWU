// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommandDrivenController.h"
#include "FCommand.h"
#include "PCControllerSlave.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API APCControllerSlave : public ACommandDrivenController
{
	GENERATED_BODY()
protected:

public:
	int slaveIndex;
};
