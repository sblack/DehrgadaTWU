// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatEffect.h"
#include "BuffBase.h"
#include "CombatEffectBuff.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UCombatEffectBuff : public UCombatEffectResistable
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Instanced, Category = Default)
		TArray<UBuffBase*> Buffs;
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void Apply(TScriptInterface<ITargetableInterface> target, class ADehrgadaTWUCharacter* user, FVector location = FVector::ZeroVector) override;
};
