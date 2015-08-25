// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "RollCalculatorCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DEHRGADATWU_API URollCalculatorCPP : public UObject
{
	GENERATED_BODY()
	
public:
	static URollCalculatorCPP* Instance;
	
	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
	void SetInstance(URollCalculatorCPP* instance);

	UFUNCTION(BlueprintImplementableEvent, Category = "Roll")
	void RollAttack(bool& result);
};
