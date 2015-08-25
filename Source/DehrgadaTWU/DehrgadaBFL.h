// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DehrgadaBFL.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UDehrgadaBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//Why is this not part of the standard library?
	UFUNCTION(BlueprintCallable, Category = "Utilities")
	static UObject* CreateObject(UClass* Class);
	
	
};
