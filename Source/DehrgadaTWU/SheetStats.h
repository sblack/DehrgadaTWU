// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SheetStats.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API USheetStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USheetStats();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 Dexterity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint8 Vitality;
};
