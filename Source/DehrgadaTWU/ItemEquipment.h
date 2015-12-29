// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ItemBase.h"
#include "ItemEquipment.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEHRGADATWU_API UItemEquipment : public UItemBase
{
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UStaticMesh* Model;

	UFUNCTION(BlueprintPure, Category = Variables)
		virtual EEquipSlot Slot() { return EEquipSlot::Head; }
};
