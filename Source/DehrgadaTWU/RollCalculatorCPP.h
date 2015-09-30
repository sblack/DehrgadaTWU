// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TargetableInterface.h"
#include "RollCalculatorCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API URollCalculatorCPP : public UObject
{
	GENERATED_BODY()
	
public:
	static URollCalculatorCPP* Instance;
	
	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Roll")
		void Attack_NoUser(const TScriptInterface<ITargetableInterface>& target, float modifier, EDefenses defense, bool& result);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Roll")
		void MeleeAttack(const TScriptInterface<ITargetableInterface>& target, class ADehrgadaTWUCharacter* user, EDefenses defense, bool& result);

	//UFUNCTION(BlueprintImplementableEvent, Category = "Roll")
	//	void RangedAttack(const TScriptInterface<ITargetableInterface>& target, class ADehrgadaTWUCharacter* user, EDefenses defense, bool& result);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Roll")
		void MagicAttack(const TScriptInterface<ITargetableInterface>& target, class ADehrgadaTWUCharacter* user, EDefenses defense, bool& result);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Roll")
		void RollDamage(int32 min, int32 max, int32& result);
};
