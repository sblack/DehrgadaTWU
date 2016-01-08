// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "ItemEquipment.h"
#include "ItemWeapon.h"
#include "FCommandAttack.h"
#include "SheetEquipment.h"

FEquipmentEntry::FEquipmentEntry()
{
	Item = nullptr;
	Durability = 0;
}


// Sets default values for this component's properties
USheetEquipment::USheetEquipment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

	/*for (int i = 0; i < 8; i++)
	{
		
	}*/
	Equipment.AddDefaulted(StatEnums::EquipSlots()->GetMaxEnumValue());
}


// Called when the game starts
void USheetEquipment::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->GetWorldTimerManager().SetTimer(timerHandle, this, &USheetEquipment::LateBeginPlay, .1f, false, .1f);
	// ...
}

void USheetEquipment::LateBeginPlay()
{
	for (int i = 0; i < Equipment.Num(); i++)
	{
		if (Equipment[i].Item == nullptr)
			continue;

		EEquipSlot slot = (EEquipSlot)i;
		if (slot >= EEquipSlot::Weapon && Equipment[i].Item->Slot() == EEquipSlot::Weapon)
		{
			ApplyEquipment(slot);
		}
		else if (slot < EEquipSlot::Weapon && Equipment[i].Item->Slot() == slot)
		{
			ApplyEquipment(slot);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s cannot be equipped to %s slot. Removed."), *Equipment[i].Item->Name.ToString(), *StatEnums::EquipSlots()->GetEnumText(i).ToString());
			Equipment[i].Item = nullptr;
		}
	}
}


// Called every frame
void USheetEquipment::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void USheetEquipment::ApplyEquipment(EEquipSlot slot)
{
	UItemEquipment* item = Equipment[(int)slot].Item;
	if (item == nullptr)
		return;

	if (item->Model)
	{
		switch (slot)
		{
		case EEquipSlot::Weapon:
			Character->RightHand->StaticMesh = item->Model;
			break;
		case EEquipSlot::AltWeapon:
			Character->LeftHand->StaticMesh = item->Model;
			break;
		default:
			break;
		}
	}

}

TArray<FCommandAttack*> USheetEquipment::GetAttackCommands()
{
	TArray<FCommandAttack*> Commands;
	bool haveWeapon = false;

	if (Equipment[(int)EEquipSlot::Weapon].Item != nullptr)
	{
		UItemWeapon* weapon = Cast<UItemWeapon>(Equipment[(int)EEquipSlot::Weapon].Item);
		for (int i = 0; i < weapon->Attacks.Num(); i++)
		{
			Commands.Add(new FCommandAttack(ITargetable(), weapon, weapon->Attacks[i])); //ITargetable() is a null targetable.
		}
		haveWeapon = true;
	}
	if (Equipment[(int)EEquipSlot::AltWeapon].Item != nullptr)
	{
		UItemWeapon* weapon = Cast<UItemWeapon>(Equipment[(int)EEquipSlot::AltWeapon].Item);
		for (int i = 0; i < weapon->Attacks.Num(); i++)
		{
			Commands.Add(new FCommandAttack(ITargetable(), weapon, weapon->Attacks[i])); //ITargetable() is a null targetable.
		}
		haveWeapon = true;
	}

	if (!haveWeapon && NaturalWeapon != nullptr)
	{
		for (int i = 0; i < NaturalWeapon->Attacks.Num(); i++)
		{
			Commands.Add(new FCommandAttack(ITargetable(), NaturalWeapon, NaturalWeapon->Attacks[i])); //ITargetable() is a null targetable.
		}
	}

	return Commands;
}