// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SheetEquipment.generated.h"

USTRUCT(BlueprintType)
struct DEHRGADATWU_API FEquipmentEntry
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UItemEquipment* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
		int32 Durability;

	FEquipmentEntry();
	//FEquipmentEntry(class UItemEquipment* Item, int32 durability = -1);
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API USheetEquipment : public UActorComponent
{
	GENERATED_BODY()
private:
	FTimerHandle timerHandle;
	void LateBeginPlay();
	//applies all the effects of the item in slot (including model)
	void ApplyEquipment(EEquipSlot slot);
public:	

	UPROPERTY(EditAnywhere, EditFixedSize, BlueprintReadWrite)
		TArray<FEquipmentEntry> Equipment;

	UPROPERTY(BlueprintReadWrite)
	class ADehrgadaTWUCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemWeapon* NaturalWeapon;

	// Sets default values for this component's properties
	USheetEquipment();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintPure, Category = Variables)
	class UItemEquipment* GetItem(EEquipSlot slot) { return Equipment[(int)slot].Item; } //the array element is never empty, so this should be fine

	UFUNCTION(BlueprintPure, Category = Variables)
		FEquipmentEntry GetEntry(EEquipSlot slot) { return Equipment[(int)slot]; }

	TArray<struct FCommandAttack*> GetAttackCommands();
};
