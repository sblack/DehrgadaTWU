// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "CombatEffect.h"
#include "ItemConsumable.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UItemConsumable : public UItemBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<UCombatEffect*> Effects;
	
	
};
