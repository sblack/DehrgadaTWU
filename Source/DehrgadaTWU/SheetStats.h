// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "StatEnums.h"
#include "DamageData.h"
#include "HealData.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FText Name;

	UPROPERTY(BlueprintReadWrite)
	class ADehrgadaTWUCharacter* Character;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<uint8> Attributes;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<uint8> AttributesTotal;

	TArray<uint8> AttributesBuff;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> Vitals;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> VitalsTotal;

	TArray<uint8> VitalsBuff;

	UPROPERTY(BlueprintReadWrite)
		TArray<int32> VitalsCurrent;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> Resists;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> ResistsTotal;

	TArray<uint8> ResistsBuff;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> Defenses;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> DefensesTotal;

	TArray<uint8> DefensesBuff;

	FReply UpdateFromDetailPanel();

	void UpdateTotals();
	void UpdateVitals();
	void UpdateResists();
	void UpdateDefenses();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void ApplyDamage(UDamageData* damage, float mult, int32 add);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void ApplyHeal(UHealData* heal);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void CheckVitals();
};
