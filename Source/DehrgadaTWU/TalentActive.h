// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Talent.h"
#include "CombatEffect.h"
#include "TalentActive.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UTalentActive : public UTalent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		bool bCanTargetActor;

	UPROPERTY(EditAnywhere)
		bool bCanTargetLocation;

	UPROPERTY(EditAnywhere, Instanced)
		TArray<UCombatEffect*> Effects;


	
};
