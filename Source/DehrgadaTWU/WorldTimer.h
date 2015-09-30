// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WorldTimer.generated.h"

UCLASS(Blueprintable)
class DEHRGADATWU_API AWorldTimer : public AActor
{
	GENERATED_BODY()
protected:
		float Time;
	
public:	
	static const float TurnLength;

	static AWorldTimer* Instance;
	// Sets default values for this actor's properties
	AWorldTimer();

	//Blueprint wants nothing to do with your useful static members, so we have to bypass it
	UFUNCTION(BlueprintCallable, Category = "Static")
		void SetInstance();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintPure, Category = "Time")
		float GetTimeSeconds() const { return Time; }
	
};
