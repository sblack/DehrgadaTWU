// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InitiativeObjectInterface.h"
#include "CombatManagerCPP.generated.h"

UENUM(BlueprintType)
enum class ERTTBState : uint8
{
	RealTime,
	PendingTB,
	TurnBased,
	PendingRT
};

UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API ACombatManagerCPP : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly)
		int32 PendingTBCounter;

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

	UPROPERTY(BlueprintReadWrite)
		ERTTBState RTTBState;

	void SetInCombat(bool inCombat);

	void ToggleRTTB();

	void PrepareForTurnBased();

	void BeginTurnBased();

	void EndTurnBased();

	void AdvanceInitiative();

	void IncrementPendingTBCounter() { PendingTBCounter++; }

	void DecrementPendingTBCounter();
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
		static void SetInCombat(bool inCombat) { ACombatManagerCPP::Instance->SetInCombat(inCombat); }

	//Reminder: gameplay only switches to TB in combat; it is RT out of combat, regardless of this value.
	UFUNCTION(BlueprintPure, Category = "Combat")
		static bool GetIsTurnBased() { return ACombatManagerCPP::Instance->RTTBState == ERTTBState::TurnBased || ACombatManagerCPP::Instance->RTTBState == ERTTBState::PendingRT; }

	UFUNCTION(BlueprintPure, Category = "Combat")
		static ERTTBState GetRTTBState() { return ACombatManagerCPP::Instance->RTTBState; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
		static void ToggleRTTB() { ACombatManagerCPP::Instance->ToggleRTTB(); }

	UFUNCTION(BlueprintPure, Category = "Combat")
		static bool GetIsTurnBasedCombat() { return GetIsTurnBased() && ACombatManagerCPP::Instance->bInCombat; }
};