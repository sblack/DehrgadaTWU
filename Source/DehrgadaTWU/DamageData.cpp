// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"
#include "DamageData.h"

void UDamageData::Damage(int32& result, float mult, int32 add)
{
	URollCalculatorCPP::Instance->RollDamage(MinDamage * mult + add, MaxDamage * mult + add, result);
}

UDamageData* UDamageData::NewDamage(EDamage damageType, EVitals targetVital, int32 minDamage, int32 maxDamage)
{
	UDamageData* ret = NewObject<UDamageData>();
	ret->DamageType = damageType;
	ret->TargetVital = targetVital;
	ret->MinDamage = (minDamage<0)?0:minDamage;
	ret->MaxDamage = (maxDamage<1)?1:maxDamage;
	if (ret->MaxDamage < ret->MinDamage)
		ret->MaxDamage = ret->MinDamage;

	return ret;
}
