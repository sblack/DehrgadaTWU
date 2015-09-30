// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TalentManagerCPP.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API ATalentManagerCPP : public AActor
{
	GENERATED_BODY()
public:
	static ATalentManagerCPP* Instance;

	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Talent")
		void Use_Location(const class UTalentActive* talent, class ADehrgadaTWUCharacter* user, FVector location) const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Talent")
		void Use_Target(const class UTalentActive* talent, class ADehrgadaTWUCharacter* user, const TScriptInterface<ITargetableInterface>& target) const;
	
};
