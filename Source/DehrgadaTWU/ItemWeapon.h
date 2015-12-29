// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemEquipment.h"
#include "ItemWeapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Sword,
	Axe,
	Bludgeon,
	Dagger,
	Fist,
	Shield,
	Staff,
	Bow,
	Gun,
	Thrown,
	Grenade,
	Improvised
};

UENUM(BlueprintType)
enum class EWeaponSize : uint8
{
	Small,
	Medium,
	Large
};

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UItemWeapon : public UItemEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EWeaponType PrimaryType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EWeaponType SecondaryType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EWeaponSize Size;

	//Attacks[0] must not be empty.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
		TArray<class UAttack*> Attacks;

	//combat effects that apply to ALL attacks with this weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UCombatEffect*> BonusEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin=0))
		float ShieldValue;

	UItemWeapon();
	
	UFUNCTION(BlueprintPure, Category = Variables)
		virtual EEquipSlot Slot() override { return EEquipSlot::Weapon; }
};
