// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InitiativeObjectInterface.h"
#include "CombatManagerCPP.generated.h"

UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API ACombatManagerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	static ACombatManagerCPP* Instance;
	
	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray< TScriptInterface<IInitiativeObjectInterface> > InitiativeQueue;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int32 CurrentInitiative;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bInCombat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsTurnBased;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void BeginTurnBased();

	void AdvanceInitiative();
};

/**
* Static access to CombatManager's variables
*/
UCLASS()
class DEHRGADATWU_API UCombatManagerBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Combat")
		static bool GetInCombat() { return ACombatManagerCPP::Instance->bInCombat; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void SetInCombat(bool inCombat) { ACombatManagerCPP::Instance->bInCombat = inCombat; }

	//Reminder: gameplay only switches to TB in combat; it is RT out of combat, regardless of this value.
	UFUNCTION(BlueprintPure, Category = "Combat")
		static bool GetIsTurnBased() { return ACombatManagerCPP::Instance->bIsTurnBased; }

	//Reminder: gameplay only switches to TB in combat; it is RT out of combat, regardless of this value.
	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void SetIsTurnBased(bool isTurnBased) { ACombatManagerCPP::Instance->bIsTurnBased = isTurnBased; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		static bool GetIsTurnBasedCombat() { return ACombatManagerCPP::Instance->bIsTurnBased && ACombatManagerCPP::Instance->bInCombat; }
};