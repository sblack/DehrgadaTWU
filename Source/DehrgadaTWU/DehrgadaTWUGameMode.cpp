// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUGameMode.h"
#include "PCControllerMaster.h"
#include "DetailCustomizations/SheetStatsCustomization.h"
#include "DetailCustomizations/SheetEquipmentCustomization.h"
#include "DehrgadaTWUCharacter.h"

ADehrgadaTWUGameMode::ADehrgadaTWUGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APCControllerMaster::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Gameplay/PCControllerMasterBP"));
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

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//Custom detail views
	PropertyModule.RegisterCustomClassLayout("SheetStats", FOnGetDetailCustomizationInstance::CreateStatic(&SheetStatsCustomization::MakeInstance));
	PropertyModule.RegisterCustomClassLayout("SheetEquipment", FOnGetDetailCustomizationInstance::CreateStatic(&SheetEquipmentCustomization::MakeInstance));
}