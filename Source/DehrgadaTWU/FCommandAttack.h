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
	class UAttack* Attack;
	class UItemWeapon* Weapon;

	FCommandAttack();
	FCommandAttack(ITargetable target);
	FCommandAttack(ITargetable target, class UItemWeapon* weapon, class UAttack* attack = nullptr);
	~FCommandAttack();

	virtual bool CanUse(class ADehrgadaTWUCharacter* user) override;

	virtual void Perform() override;

	virtual void Resolve() override;
};
