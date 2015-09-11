// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "FCommand.h"
#include "FCommandAttack.h"
#include "CommandsBFL.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UCommandsBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	//Generates Command: move to location and stop
	UFUNCTION(BlueprintCallable, Category = "Command")
		static FCommand MoveTo(FVector location);
	//Generates Command: move/follow pawn until close
	UFUNCTION(BlueprintCallable, Category = "Command")
		static FCommand Approach(TScriptInterface<ITargetableInterface> target);
	//Generates Attack Command
	UFUNCTION(BlueprintCallable, Category = "Command")
		static FCommandAttack Attack(TScriptInterface<ITargetableInterface> target);
};
