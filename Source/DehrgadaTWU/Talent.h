// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "Talent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract, Const)
class DEHRGADATWU_API UTalent : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;
	
};
