// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "Talent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract, Const)
class DEHRGADATWU_API UTalent : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Description;
	
};

//sb110315 - considering renaming this to TalentActive and TalentActive to TalentInstant
/**
 *
 */
UCLASS(BlueprintType, Abstract, Const)
class DEHRGADATWU_API UTalentNonPassive : public UTalent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0), Category = "Costs")
		int32 HealthCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0), Category = "Costs")
		int32 ClarityCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0), Category = "Costs")
		int32 StaminaCost;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsSelf;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsAllies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsLiving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsDying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Affects")
		bool bAffectsObjects;

public:
	UFUNCTION(BlueprintPure, Category = "Talents")
		int32 VitalCost(EVitals vital);

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectSelf() { return bAffectsSelf; }

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectAllies() { return bAffectsAllies; }

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectEnemies() { return bAffectsEnemies; }

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectLiving() { return bAffectsLiving; }

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectDying() { return bAffectsDying; }

	UFUNCTION(BlueprintPure, Category = "Talents")
		bool CanAffectObjects() { return bAffectsObjects; }
};
