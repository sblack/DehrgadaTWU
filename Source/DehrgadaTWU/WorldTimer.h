// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldTimer.generated.h"

UCLASS(Blueprintable)
class DEHRGADATWU_API AWorldTimer : public AActor
{
	GENERATED_BODY()

		friend class UWorldTimerBFL;
protected:
		float Time;
	
public:	
	static const float TurnLength;

	static AWorldTimer* Instance;
	// Sets default values for this actor's properties
	AWorldTimer();

	bool bIsRunning;

	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	float GetTimeSeconds() const { return Time; }

	void AdvanceOneTurn() { Time += TurnLength; }
};

/**
* Static access to WorldTimer's variables
*/
UCLASS()
class DEHRGADATWU_API UWorldTimerBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Time")
		static float GetWorldTime() { return AWorldTimer::Instance->Time; }

	UFUNCTION(BlueprintPure, Category = "Time")
		static float GetTurnLength() { return AWorldTimer::TurnLength; }
};
