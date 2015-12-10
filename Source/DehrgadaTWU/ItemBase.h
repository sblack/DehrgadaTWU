// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Const)
class DEHRGADATWU_API UItemBase : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText PickupText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText ActionText;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UTexture2D* ItemImage;
	
};
