// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUGameMode.h"
#include "PCControllerMaster.h"
#include "DehrgadaTWUCharacter.h"

ADehrgadaTWUGameMode::ADehrgadaTWUGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APCControllerMaster::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/PCControllerMasterBP"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}