// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DehrgadaTWU.h"
#include "SheetStats.h"
#include "SheetTalents.h"
#include "SheetBuffs.h"
#include "SheetEquipment.h"
#include "DehrgadaTWUCharacter.h"

ADehrgadaTWUCharacter::ADehrgadaTWUCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	LeftHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHand"));
	LeftHand->AttachTo(GetMesh(), "accessory_L1_SKL");
	RightHand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHand"));
	RightHand->AttachTo(GetMesh(), "accessory_R1_SKL");
}

void ADehrgadaTWUCharacter::BeginPlay()
{
	Super::BeginPlay();

	Stats = (USheetStats*)GetComponentByClass(USheetStats::StaticClass());
	Stats->Character = this;

	Talents = (USheetTalents*)GetComponentByClass(USheetTalents::StaticClass());
	Talents->Character = this;

	Buffs = (USheetBuffs*)GetComponentByClass(USheetBuffs::StaticClass());
	Buffs->Character = this;

	Equipment = (USheetEquipment*)GetComponentByClass(USheetEquipment::StaticClass());
	Equipment->Character = this;
}

void ADehrgadaTWUCharacter::ApplyDamage(UDamageData* damage, float mult, int32 add)
{
	Stats->ApplyDamage(damage, mult, add);
}

void ADehrgadaTWUCharacter::ApplyHeal(UHealData* heal)
{
	Stats->ApplyHeal(heal);
}

void ADehrgadaTWUCharacter::ApplyBuff(UBuffBase* buff)
{
	Buffs->ApplyBuff(buff);
}

void ADehrgadaTWUCharacter::RemoveBuff(UBuffBase* buff)
{
	Buffs->RemoveBuff(buff);
}

float ADehrgadaTWUCharacter::GetDefense(EDefenses defense) const
{
	return Stats->DefensesTotal[(int)defense] + 10.f;
}