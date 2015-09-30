// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "CameraPawn.h"
#include "FCommand.h"
#include "FCommandAttack.h"
#include "CommandMenuCPP.h"
#include "CombatManagerCPP.h"
//#include "Engine.h"
#include "EngineUtils.h"
#include "PCControllerMaster.h"

APCControllerMaster* APCControllerMaster::Instance;

APCControllerMaster::APCControllerMaster()
{
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	Instance = this;
}

void APCControllerMaster::BeginPlay()
{
	Super::BeginPlay();

	CameraPawn = (ACameraPawn*)GetPawn();

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APCControllerSlave::StaticClass(), temp);
	for (int i = 0; i < temp.Num(); i++)
	{
		Slaves.Add((APCControllerSlave*)(temp[i]));
		((APCControllerSlave*)(temp[i]))->slaveIndex = i;
	}

	AttachCamera();
}

void APCControllerMaster::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APCControllerMaster::OnLeftClickDown);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APCControllerMaster::OnLeftClickUp);
	InputComponent->BindAction("RightClick", IE_Released, this, &APCControllerMaster::OnRightClickUp);

	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &APCControllerMaster::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &APCControllerMaster::ZoomOut);

	InputComponent->BindAction("ReattachCamera", IE_Pressed, this, &APCControllerMaster::AttachCamera);

	InputComponent->BindAxis("MoveForward", this, &APCControllerMaster::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APCControllerMaster::MoveRight);
	InputComponent->BindAxis("RotateCamera", this, &APCControllerMaster::RotateCamera);
}

void APCControllerMaster::AttachCamera()
{
	CameraPawn->AttachCamera(ActiveCharacter());
	OnActiveCharacterChanged();
}

void APCControllerMaster::OnLeftClickDown()
{
}

void APCControllerMaster::OnLeftClickUp()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Camera, false, Hit);

	if (!Hit.bBlockingHit) return;

	if (Hit.Actor->ActorHasTag(FName("Terrain")))
	{
		//UE_LOG(LogTemp, Log, TEXT("%s"),*Hit.Location.ToString());
		Slaves[CurrentSlave]->ReceiveCommand(new FCommand(Hit.Location));
	}
	else if (Hit.Actor->GetClass()->ImplementsInterface(UTargetableInterface::StaticClass()))
	{
		if (Hit.Actor->ActorHasTag(FName("Party")))
		{
			if (!UCombatManagerBFL::GetIsTurnBasedCombat())
			{
				AController* temp = ((APawn*)(Hit.GetActor()))->GetController();
				CurrentSlave = ((APCControllerSlave*)temp)->slaveIndex;
				AttachCamera();
			}
		}
		else if (Hit.Actor->ActorHasTag(FName("Enemy")))
		{
			Slaves[CurrentSlave]->ReceiveCommand(new FCommandAttack(ITargetableInterface::Targetable(Hit.GetActor())));
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("%s has no Left Click-relevant tag"), *Hit.Actor->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s is neither terrain nor targetable"), *Hit.Actor->GetName());
	}
}

void APCControllerMaster::OnRightClickUp()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Camera, false, Hit);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Right Click"));

	if (!Hit.bBlockingHit) return;

	if (Hit.Actor->ActorHasTag(FName("Terrain")))
	{
		OpenCommandMenu(Slaves[CurrentSlave]->GetDehrgadaTWUCharacter());
		CommandMenu->Prepare(Hit.Location);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Terrain"));
	}
	else if (Hit.Actor->GetClass()->ImplementsInterface(UTargetableInterface::StaticClass()))
	{
		OpenCommandMenu(Slaves[CurrentSlave]->GetDehrgadaTWUCharacter());
		CommandMenu->Prepare(ITargetableInterface::Targetable(Hit.GetActor()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Not Terrain"));
	}
}

void APCControllerMaster::ZoomIn()
{
	CameraPawn->ZoomIn();
}

void APCControllerMaster::ZoomOut()
{
	CameraPawn->ZoomOut();
}

void APCControllerMaster::MoveForward(float value)
{
	CameraPawn->MoveForward(value);
}

void APCControllerMaster::MoveRight(float value)
{
	CameraPawn->MoveRight(value);
}

void APCControllerMaster::RotateCamera(float value)
{
	CameraPawn->RotateCamera(value);
}

void APCControllerMaster::ReceiveCommandFromGUI(FCommand* command)
{
	Slaves[CurrentSlave]->ReceiveCommand(command);
}

ADehrgadaTWUCharacter* APCControllerMaster::ActiveCharacter()
{
	return Slaves[CurrentSlave]->GetDehrgadaTWUCharacter();
}

void APCControllerMaster::SwitchToSlave(int slaveIndex)
{
	if (Slaves.IsValidIndex(slaveIndex))
	{
		CurrentSlave = slaveIndex;
		OnActiveCharacterChanged();
	}
}