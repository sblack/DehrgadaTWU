// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "AreaOfEffect.h"
#include "Talent.h"

int32 UTalentNonPassive::VitalCost(EVitals vital)
{
	switch (vital)
	{
	case EVitals::Health:
		return HealthCost;
	case EVitals::Clarity:
		return ClarityCost;
	case EVitals::Stamina:
		return StaminaCost;
	default:
		return 0;
	}
}