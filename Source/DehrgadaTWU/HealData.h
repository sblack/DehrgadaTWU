// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "HealData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class DEHRGADATWU_API UHealData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EVitals TargetVital;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
		int32 Amount;
	
	static UHealData* NewHeal(EVitals targetVital, int32 amount);
	
};
