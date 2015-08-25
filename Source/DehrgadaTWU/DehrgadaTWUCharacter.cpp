// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DehrgadaTWU.h"
#include "SheetStats.h"
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
}

void ADehrgadaTWUCharacter::BeginPlay()
{
	Stats = (USheetStats*)GetComponentByClass(USheetStats::StaticClass());
}