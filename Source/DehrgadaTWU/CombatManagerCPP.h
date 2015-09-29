// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CombatManagerCPP.generated.h"

UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API ACombatManagerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	static ACombatManagerCPP* Instance;
	
	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance(ACombatManagerCPP* instance);

};
