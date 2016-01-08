// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Attack.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, BlueprintType)
class DEHRGADATWU_API UAttack : public UObject
{
	GENERATED_BODY()
public:

	UAttack();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CritMult = 2.0f;
	//percentage
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CritRange = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Range = 150;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float RangeFalloff = .20f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BaseAP = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsMelee;

	//public AmmoUsage usage = AmmoUsage.Free;
	//public AttributeName ? damageAttribute = null;
	//public GameObject projectile;

	//if true, certain CombatEffects (currently only Damage) will be applied at half effect on a miss. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AttackRoll")
		bool bHalfOnMiss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<class UCombatEffect*> Effects;

	//Rolls are made (and effects applied) until one misses.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<class UAttackRoll*> SubsequentRolls;
};
