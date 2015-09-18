// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "HealData.h"

UHealData* UHealData::NewHeal(EVitals targetVital, int32 amount)
{
	UHealData* ret = NewObject<UHealData>();
	ret->TargetVital = targetVital;
	ret->Amount = amount;

	return ret;
}


