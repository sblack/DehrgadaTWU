// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FogOfWarManager.h"
#include "FogOfWarViewer.h"


// Sets default values for this component's properties
UFogOfWarViewer::UFogOfWarViewer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFogOfWarViewer::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetWorldTimerManager().SetTimer(timerHandle, this, &UFogOfWarViewer::LateBeginPlay, .1f, false, .1f);
}

void UFogOfWarViewer::LateBeginPlay()
{
	if (AFogOfWarManager::Instance == nullptr)
	{
		return;
	}

	AFogOfWarManager::Instance->RegisterFowViewer(this);
	// ...	
	sightRadiusSq = sightRadius * sightRadius;
	int temp = 9 * sightRadius;
	scanAngle = PI * 2 / temp;
	for (int i = 0; i < temp; i++)
	{
		scanPoints.Add(FVector(cosf(scanAngle*i), sinf(scanAngle*i), 0) * sightRadius * 100);
	}
}


// Called every frame
void UFogOfWarViewer::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

