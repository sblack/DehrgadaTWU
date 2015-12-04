// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FogOfWarLight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API UFogOfWarLight : public UActorComponent
{
	GENERATED_BODY()

	FTimerHandle timerHandle;
	void LateBeginPlay();
public:	
	// Sets default values for this component's properties
	UFogOfWarLight();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 1))
		float intensity = 1;

	//in meters
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 1))
		float lightRadius = 1;

	UPROPERTY(BlueprintReadOnly)
		float lightRadiusSq;

	//in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 360))
		float angle;

	UPROPERTY()
		TArray<FVector> scanPoints;

	UPROPERTY()
		float scanAngle;

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
