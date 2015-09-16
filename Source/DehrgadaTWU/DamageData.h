// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "DamageData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class DEHRGADATWU_API UDamageData : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EDamage DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EVitals TargetVital;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
		int32 MinDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
		int32 MaxDamage;
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
		void Damage(int32& result, float mult = 1.f, int32 add = 0);

	static UDamageData* NewDamage(EDamage damageType, EVitals targetVital, int32 minDamage, int32 maxDamage);
};
