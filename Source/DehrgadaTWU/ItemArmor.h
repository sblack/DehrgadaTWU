// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemEquipment.h"
#include "ItemArmor.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UItemArmor : public UItemEquipment
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		EArmorSlot ArmorSlot;
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin = 1))
		int32 ArmorValue;

	UFUNCTION(BlueprintPure, Category = Variables)
		virtual EEquipSlot Slot() override { return (EEquipSlot)ArmorSlot; }
	
};
