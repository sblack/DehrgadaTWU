// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatEffect.h"
#include "DamageData.h"
#include "CombatEffectDamage.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UCombatEffectDamage : public UCombatEffect
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Instanced, Category = Default)
		TArray<UDamageData*> Damage;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void ApplyHalf(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply_MA(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, float mult, int32 add);
};
