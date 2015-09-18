// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TargetableInterface.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class DEHRGADATWU_API UTargetableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class DEHRGADATWU_API ITargetableInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	AActor* AsActor() const { return Cast<AActor>(_getUObject()); }
	FVector Location() const { return AsActor()->GetActorLocation(); }

	virtual void ApplyDamage(class UDamageData* damage, float mult, int32 add) {}
	virtual void ApplyHeal(class UHealData* heal) {}

	UFUNCTION(BlueprintCallable, Category = "Target")
		virtual float GetDefense(EDefenses defense) const { return 5.f; }

	static TScriptInterface<ITargetableInterface> Targetable(AActor* actor);
};

typedef TScriptInterface<ITargetableInterface> ITargetable;