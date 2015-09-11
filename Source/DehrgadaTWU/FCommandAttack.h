// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCommand.h"
#include "FCommandAttack.generated.h"

/**
 * 
 */
USTRUCT()
struct DEHRGADATWU_API FCommandAttack : public FCommand
{
	GENERATED_USTRUCT_BODY()
public:
	FCommandAttack();
	FCommandAttack(ITargetable target);
	~FCommandAttack();

	virtual void Perform() override;

	virtual void Resolve() override;
};
