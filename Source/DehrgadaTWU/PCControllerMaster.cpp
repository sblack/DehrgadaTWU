// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "PCControllerSlave.h"
#include "CameraPawn.h"
#include "FCommand.h"
#include "FCommandAttack.h"
#include "CommandMenuCPP.h"
#include <vector>
#include "Engine.h"
#include "EngineUtils.h"
#include "PCControllerMaster.h"

APCControllerMaster::APCControllerMaster()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	CameraForward = FVector::ForwardVector;
	CameraRight = FVector::RightVector;
}

void APCControllerMaster::BeginPlay()
{
	Super::BeginPlay();

	CameraPawn = (ACameraPawn*)GetPawn();

	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APCControllerSlave::StaticClass(), temp);
	for (int i = 0; i < temp.Num(); i++)
	{
		Slaves.insert(Slaves.end(), (APCControllerSlave*)(temp[i]));
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
	APCControllerSlave* slave = Slaves[CurrentSlave];
	CameraPawn->AttachRootComponentToActor(slave->GetPawn(), NAME_None, EAttachLocation::SnapToTarget);
	CameraPawn->SetActorRotation(CameraForward.Rotation() + FRotator(-60, 0, 0));
	bFreeCamera = false;
}

void APCControllerMaster::ReleaseCamera()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Release!"));
	CameraPawn->DetachRootComponentFromParent();
	CameraPawn->DetachRootComponentFromParent();
	CameraPawn->DetachRootComponentFromParent();

	CameraPawn->DetachRootComponentFromParent();
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
	else if (Hit.Actor->ActorHasTag(FName("Party")))
	{
		AController* temp = ((APawn*)(Hit.GetActor()))->GetController();
		CurrentSlave = ((APCControllerSlave*)temp)->slaveIndex;
		AttachCamera();
	}
	else if (Hit.Actor->ActorHasTag(FName("Enemy")))
	{
		Slaves[CurrentSlave]->ReceiveCommand(new FCommandAttack((APawn*)(Hit.GetActor())));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s has no Left Click-relevant tag"), *Hit.Actor->GetName());
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
		OpenCommandMenu();
		CommandMenu->Prepare(Hit.Location);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Terrain"));
	}
	else
	{
		OpenCommandMenu();
		CommandMenu->Prepare(Hit.GetActor());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Not Terrain"));
	}
}

void APCControllerMaster::ZoomIn()
{
	float armLength = CameraPawn->GetCameraBoom()->TargetArmLength - 25.0f;
	if (armLength < 500.0f)
		armLength = 500.0f;
	CameraPawn->GetCameraBoom()->TargetArmLength = armLength;
}

void APCControllerMaster::ZoomOut()
{
	float armLength = CameraPawn->GetCameraBoom()->TargetArmLength + 25.0f;
	if (armLength > 1500.0f)
		armLength = 1500.0f;
	CameraPawn->GetCameraBoom()->TargetArmLength = armLength;
}

void APCControllerMaster::MoveForward(float value)
{
	if (value == 0) return;
	if (!bFreeCamera)
	{
		ReleaseCamera();
		bFreeCamera = true;
	}
	FVector vec = CameraForward * value;
	CameraPawn->SetActorLocation(CameraPawn->GetActorLocation() + vec);
}

void APCControllerMaster::MoveRight(float value)
{
	if (value == 0) return;
	if (!bFreeCamera)
	{
		ReleaseCamera();
		bFreeCamera = true;
	}
	FVector vec = CameraRight * value;
	CameraPawn->SetActorLocation(CameraPawn->GetActorLocation() + vec);
}

void APCControllerMaster::RotateCamera(float value)
{
	if (value == 0) return;
	CameraForward = CameraForward.RotateAngleAxis(value, FVector::UpVector);
	CameraRight = CameraRight.RotateAngleAxis(value, FVector::UpVector);
	CameraPawn->SetActorRotation(CameraForward.Rotation() + FRotator(-60, 0, 0));
}

void APCControllerMaster::ReceiveCommandFromGUI(FCommand* command)
{
	Slaves[CurrentSlave]->ReceiveCommand(command);
}
