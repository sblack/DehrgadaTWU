// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCommand.h"

/**
 * 
 */
class DEHRGADATWU_API FCommandAttack : public FCommand
{
public:
	FCommandAttack(class APawn* pawn);
	~FCommandAttack();

	virtual void Perform() override;

	virtual void Resolve() override;
};
