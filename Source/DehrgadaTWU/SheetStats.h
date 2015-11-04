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

	TArray<int32> AttributesBuff;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> Vitals;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<int32> VitalsTotal;

	TArray<int32> VitalsBuff;

	UPROPERTY(BlueprintReadWrite)
		TArray<int32> VitalsCurrent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float APTotal;

	float APBuff;

	UPROPERTY(BlueprintReadWrite)
		float APCurrent;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> Resists;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> ResistsTotal;

	TArray<float> ResistsBuff;

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> Defenses;

	UPROPERTY(VisibleAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<float> DefensesTotal;

	TArray<float> DefensesBuff;

	FReply UpdateFromDetailPanel();

	void UpdateTotals();
	void UpdateVitals();
	void UpdateResists();
	void UpdateDefenses();

	void UpdateAPForNewTurn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void ApplyDamage(UDamageData* damage, float mult, int32 add);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void ApplyHeal(UHealData* heal);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void CheckVitals();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Vitals")
		void SpendVitals(const class UTalentActive* talent);
};
