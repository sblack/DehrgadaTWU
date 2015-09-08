// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Talent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Const, Abstract)
class DEHRGADATWU_API UTalent : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FText Name;
	
	
};
