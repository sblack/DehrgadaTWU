// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "GameFramework/PlayerController.h"
#include "FCommand.h"
#include "PCControllerMaster.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API APCControllerMaster : public APlayerController
{
	GENERATED_BODY()
public:
	APCControllerMaster();

	void ReceiveCommandFromGUI(FCommand* command);

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void AttachCamera();
	void ReleaseCamera();

	void OnLeftClickDown();
	void OnLeftClickUp();
	void OnRightClickUp();
	void ZoomIn();
	void ZoomOut();
	void MoveForward(float value);
	void MoveRight(float value);
	void RotateCamera(float value);

	UFUNCTION(BlueprintImplementableEvent, Category = "Commands")
	void OpenCommandMenu(class ADehrgadaTWUCharacter* activeCharacter);

	UPROPERTY(BlueprintReadWrite, Category = "Commands")
	class UCommandMenuCPP* CommandMenu;

	UFUNCTION(BlueprintPure, Category = "Default")
	class ADehrgadaTWUCharacter* ActiveCharacter();

	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
		void OnActiveCharacterChanged();

	class ACameraPawn* CameraPawn;

	std::vector<class APCControllerSlave*> Slaves;

	int CurrentSlave = 0;

	bool bFreeCamera;

	//Because I apparently have to wipe Unreal's ass for it
	FVector CameraForward;
	FVector CameraRight;
};
