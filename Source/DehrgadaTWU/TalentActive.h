// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Talent.h"
#include "CombatEffect.h"
#include "TalentActive.generated.h"

UENUM(BlueprintType)
enum class EAreaShape : uint8 //sb091715 - if you somehow come up with more than 256 shapes, designers: I WILL HURT YOU.
{
	SingleTarget,
	Sphere,
	Aura,
	Ray,
	Cone
};

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UTalentActive : public UTalent
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		int32 HealthCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		int32 ClarityCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		int32 StaminaCost;

	UFUNCTION(BlueprintPure, Category = "Talents")
		int32 VitalCost(EVitals vital);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float APCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bCanTargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bCanTargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<UCombatEffect*> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EAreaShape Shape;

	//doubles as length, where appropriate
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0, ClampMax = 360))
		float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UParticleSystem* OnHitParticles;
};
