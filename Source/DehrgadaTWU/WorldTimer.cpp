// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatManagerCPP.h"
#include "WorldTimer.h"

const float AWorldTimer::TurnLength = 5.f;
AWorldTimer* AWorldTimer::Instance;

// Sets default values
AWorldTimer::AWorldTimer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsRunning = true;
}

void AWorldTimer::SetInstance()
{
	Instance = this;
}

// Called when the game starts or when spawned
void AWorldTimer::BeginPlay()
{
	Super::BeginPlay();
	//TODO: grab the time from save file
}

// Called every frame
void AWorldTimer::Tick( float DeltaTime )
{
	if (!bIsRunning)
	{
		return;
	}
	Super::Tick( DeltaTime );
	Time += DeltaTime;
}

