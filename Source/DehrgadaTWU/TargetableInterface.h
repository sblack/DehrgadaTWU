// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TargetableInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
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

	static TScriptInterface<ITargetableInterface> Targetable(AActor* actor);
};

typedef TScriptInterface<ITargetableInterface> ITargetable;