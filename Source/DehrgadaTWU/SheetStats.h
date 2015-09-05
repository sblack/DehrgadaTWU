// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "StatEnums.h"
#include "SheetStats.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEHRGADATWU_API USheetStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USheetStats();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	//virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintReadWrite)
	class ADehrgadaTWUCharacter* Character;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<uint8> Attributes;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<uint8> AttributesTotal;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> Vitals;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> VitalsTotal;

	UPROPERTY(BlueprintReadWrite)
		TArray<int32> VitalsCurrent;

	FReply UpdateFromDetailPanel();

	void UpdateTotals();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void ApplyDamage(int32 damage, EVitals targetVital);
};
