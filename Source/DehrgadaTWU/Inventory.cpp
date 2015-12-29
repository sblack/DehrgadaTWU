// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "Inventory.h"

FInventoryEntry::FInventoryEntry()
{
}

FInventoryEntry::FInventoryEntry(UItemBase* item, int32 count)
{
	Item = item;
	Count = count;
}

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

FInventoryEntry UInventory::GetItem(int32 index)
{
	if (Items.IsValidIndex(index))
		return Items[index];
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BAD INDEX"));
		UE_LOG(LogInventory, Error, TEXT("GetItem: Bad index: %d"), index);
		return FInventoryEntry();
	}
}

int32 UInventory::HasItem(UItemBase* item)
{
	if (item == nullptr)
		return -1;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Item == item)
		{
			return i;
		}
	}

	return -1;
}

void UInventory::AddItem(UItemBase* item, int32 count)
{
	if (count < 1 || item == nullptr)
		return;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Item == item)
		{
			Items[i].Count += count;
			return;
		}
	}

	Items.Add(FInventoryEntry(item, count));
}

void UInventory::AddItem_Entry(FInventoryEntry entry)
{
	AddItem(entry.Item, entry.Count);
}

void UInventory::RemoveItem(UItemBase* item, int32 count)
{
	if (count < 1 || item == nullptr)
		return;

	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Item == item)
		{
			if (count == -1)
			{
				Items.RemoveAt(i);
			}
			else
			{
				Items[i].Count -= count;
				if (Items[i].Count < 1)
					Items.RemoveAt(i);
			}
			return;
		}
	}
}

void UInventory::RemoveIndex(int32 index, int32 count)
{
	if (count < 1)
		return;
	if (Items.IsValidIndex(index))
	{
		if (count == -1)
		{
			Items.RemoveAt(index);
		}
		else
		{
			Items[index].Count -= count;
			if (Items[index].Count < 1)
				Items.RemoveAt(index);
		}
	}
	else
	{
		UE_LOG(LogInventory, Error, TEXT("RemoveIndex: Bad index: %d"), index);
	}
}