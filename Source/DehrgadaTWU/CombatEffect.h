// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "CombatEffect.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType)
class DEHRGADATWU_API UCombatEffect : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual bool AttackRoll(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user) { return true; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual bool AttackRoll_NoUser(TScriptInterface<ITargetableInterface> target, float attackMod) { return true; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) {}
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Remove(TScriptInterface<ITargetableInterface> target) {}
	
};

UCLASS(Abstract)
class DEHRGADATWU_API UCombatEffectResistable : public UCombatEffect
{
	GENERATED_BODY()
public:
	//If true, CombatEffect always hits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		bool bNoDefense;
	//If false, use weave attack roll. Ranged only ever uses projectiles, so this never applies to them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		bool bUseMeleeAttackRoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
		EDefenses Defense;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual bool AttackRoll(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user) override;
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual bool AttackRoll_NoUser(TScriptInterface<ITargetableInterface> target, float attackMod) override;
};