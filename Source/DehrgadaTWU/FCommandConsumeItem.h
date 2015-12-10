// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCommand.h"
#include "FCommandConsumeItem.generated.h"

/**
 * 
 */
USTRUCT()
struct DEHRGADATWU_API FCommandConsumeItem : public FCommand
{
	GENERATED_USTRUCT_BODY()
public:
	//TODO: should be replaced with InventoryEntry, whenever that gets added
	UPROPERTY(BlueprintReadOnly)
	class UItemConsumable* Item;
	
	FCommandConsumeItem();
	FCommandConsumeItem(class UItemConsumable* item);

	virtual void Perform() override;
	virtual void Resolve() override;
	
	
};
