// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FogOfWarManager.h"
#include "FogOfWarLight.h"


// Sets default values for this component's properties
UFogOfWarLight::UFogOfWarLight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	angle = 360;
	// ...
}


// Called when the game starts
void UFogOfWarLight::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetWorldTimerManager().SetTimer(timerHandle, this, &UFogOfWarLight::LateBeginPlay, .05f, false, .05f);
}

void UFogOfWarLight::LateBeginPlay()
{
	if (AFogOfWarManager::Instance == nullptr)
	{
		return;
	}

	lightRadiusSq = lightRadius * lightRadius;
	int temp = 9 * lightRadius;
	scanAngle = PI * 2 / temp;
	for (int i = 0; i < temp; i++)
	{
		scanPoints.Add(FVector(cosf(scanAngle*i), sinf(scanAngle*i), 0) * lightRadius * 100);
	}

	if (GetOwner()->GetRootComponent()->Mobility == EComponentMobility::Movable)
		AFogOfWarManager::Instance->RegisterFowLight(this);
	else
		AFogOfWarManager::Instance->UpdateStaticLight(this, true);
}


// Called every frame
void UFogOfWarLight::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

