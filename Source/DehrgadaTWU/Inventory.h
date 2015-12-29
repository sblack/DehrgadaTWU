// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "Inventory.generated.h"

USTRUCT(BlueprintType)
struct DEHRGADATWU_API FInventoryEntry
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UItemBase* Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0))
		int32 Count;

	FInventoryEntry();
	FInventoryEntry(UItemBase* item, int32 count = 1);
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryEntry> Items;

	// Sets default values for this component's properties
	UInventory();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintPure, Category = Inventory)
		int32 GetSize() { return Items.Num(); }

	UFUNCTION(BlueprintPure, Category = Inventory)
		FInventoryEntry GetItem(int32 index);

	//returns index of item, or -1 if not found
	UFUNCTION(BlueprintPure, Category = Inventory)
		int32 HasItem(UItemBase* item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void AddItem(UItemBase* item, int32 count = 1);

	UFUNCTION(BlueprintCallable, Category = Inventory)
		void AddItem_Entry(FInventoryEntry entry);
	
	//count = -1 to remove all of the item
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void RemoveItem(UItemBase* item, int32 count = 1);

	//count = -1 to remove all of the item
	UFUNCTION(BlueprintCallable, Category = Inventory)
		void RemoveIndex(int32 index, int32 count = 1);
};
