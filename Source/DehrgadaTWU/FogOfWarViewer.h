// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FogOfWarViewer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API UFogOfWarViewer : public UActorComponent
{
	GENERATED_BODY()
		
	FTimerHandle timerHandle;
	void LateBeginPlay();
public:	
	// Sets default values for this component's properties
	UFogOfWarViewer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin = 1))
		float sightRadius = 1; //Meters
	UPROPERTY(BlueprintReadOnly)
		float sightRadiusSq;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bLowLightVision;

	UPROPERTY()
		TArray<FVector> scanPoints;

	UPROPERTY()
		float scanAngle;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
