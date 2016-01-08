// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "AttackRoll.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, BlueprintType)
class DEHRGADATWU_API UAttackRoll : public UObject
{
	GENERATED_BODY()
public:
	//"attack" always hits. Use this for talents meant for the user or allies.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAutoHit;

	//if true, certain CombatEffects (currently only Damage) will be applied at half effect on a miss.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bAutoHit"))
		bool bHalfOnMiss;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "!bAutoHit"))
		EDefenses Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<class UCombatEffect*> Effects;


	UFUNCTION(BlueprintCallable, Category = "Attack")
		bool RollAttack(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user);

	UFUNCTION(BlueprintCallable, Category = "Attack")
		bool RollAttack_NoUser(TScriptInterface<ITargetableInterface> target, float attackBonus);

	UFUNCTION(BlueprintCallable, Category = "Attack")
		static void RollAttacks(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, TArray<UAttackRoll*> attacks, FVector location = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "Attack")
		static void RollAttacks_NoUser(TScriptInterface<ITargetableInterface> target, float attackBonus, TArray<UAttackRoll*> attacks, FVector location = FVector::ZeroVector);
};
