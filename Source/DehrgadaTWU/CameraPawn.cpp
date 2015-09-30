// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "CameraPawn.h"

ACameraPawn* ACameraPawn::Instance;

// Sets default values
ACameraPawn::ACameraPawn()
{
	Instance = this;
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does. LOL UNREAL DOES IT ANYWAY
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f); //This line is fucking pointless due to the way actor attachment works
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	CameraForward = FVector::ForwardVector;
	CameraRight = FVector::RightVector;

	bLocked = false;
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraPawn::AttachCamera(ADehrgadaTWUCharacter* actor)
{
	AttachRootComponentToActor(actor, NAME_None, EAttachLocation::SnapToTarget);
	SetActorRotation(CameraForward.Rotation() + FRotator(-60, 0, 0));
	bFreeCamera = false;
}

void ACameraPawn::ReleaseCamera()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Release!"));
	DetachRootComponentFromParent();
	//CameraPawn->DetachRootComponentFromParent();
	//CameraPawn->DetachRootComponentFromParent();

	//CameraPawn->DetachRootComponentFromParent();
}

void ACameraPawn::ZoomIn()
{
	float armLength = GetCameraBoom()->TargetArmLength - 25.0f;
	if (armLength < 500.0f)
		armLength = 500.0f;
	GetCameraBoom()->TargetArmLength = armLength;
}

void ACameraPawn::ZoomOut()
{
	float armLength = GetCameraBoom()->TargetArmLength + 25.0f;
	if (armLength > 1500.0f)
		armLength = 1500.0f;
	GetCameraBoom()->TargetArmLength = armLength;
}

void ACameraPawn::MoveForward(float value)
{
	if (value == 0) return;
	if (!bFreeCamera)
	{
		ReleaseCamera();
		bFreeCamera = true;
	}
	FVector vec = CameraForward * value;
	SetActorLocation(GetActorLocation() + vec);
}

void ACameraPawn::MoveRight(float value)
{
	if (value == 0) return;
	if (!bFreeCamera)
	{
		ReleaseCamera();
		bFreeCamera = true;
	}
	FVector vec = CameraRight * value;
	SetActorLocation(GetActorLocation() + vec);
}

void ACameraPawn::RotateCamera(float value)
{
	if (value == 0) return;
	CameraForward = CameraForward.RotateAngleAxis(value, FVector::UpVector);
	CameraRight = CameraRight.RotateAngleAxis(value, FVector::UpVector);
	SetActorRotation(CameraForward.Rotation() + FRotator(-60, 0, 0));
}