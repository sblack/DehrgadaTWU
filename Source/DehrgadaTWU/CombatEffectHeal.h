// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatEffect.h"
#include "HealData.h"
#include "CombatEffectHeal.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UCombatEffectHeal : public UCombatEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Instanced, Category = Default)
		TArray<UHealData*> Heal;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) override;
	
};
