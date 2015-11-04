// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Talent.h"
#include "CombatEffect.h"
#include "TalentModal.generated.h"

/**
 * 
 */
UCLASS(HideCategories = ("Affects"))
class DEHRGADATWU_API UTalentModal : public UTalentNonPassive
{
	GENERATED_BODY()
public:

	UTalentModal();

	//A character can not have more than one Mode of the same set active at a time. Modes with no set are unrestricted.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString ModalSet;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<UCombatEffect*> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* OnActivateParticles;
	
};

/**
 *
 */
UCLASS(ShowCategories = ("Affects"))
class DEHRGADATWU_API UTalentAura : public UTalentModal
{
	GENERATED_BODY()
public:
	//Final Radius is Base + Mult * Clout
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float RadiusBase;
	//Final Radius is Base + Mult * Clout
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float RadiusMult;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UMaterialInterface* Decal;
};