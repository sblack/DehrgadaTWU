// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "CombatEffect.generated.h"

class UCombatEffectHalvable;

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType)
class DEHRGADATWU_API UCombatEffect : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) {}
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void ApplyHalf(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) {}
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Remove(TScriptInterface<ITargetableInterface> target) {}
	

	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void ApplyEffects(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void ApplyEffectsHalf(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector);
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void RemoveEffects(TScriptInterface<ITargetableInterface> target, TArray<UCombatEffect*> effects);
};