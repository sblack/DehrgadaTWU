// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class DEHRGADATWU_API ACameraPawn : public APawn
{
	GENERATED_BODY()
protected:
	bool bFreeCamera;
	//Because I apparently have to wipe Unreal's ass for it
	FVector CameraForward;
	FVector CameraRight;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	static ACameraPawn* Instance;
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void AttachCamera(class ADehrgadaTWUCharacter* actor);
	void ReleaseCamera();

	void ZoomIn();
	void ZoomOut();
	void MoveForward(float value);
	void MoveRight(float value);
	void RotateCamera(float value);

	//if true, the camera will not respond to player inputs
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bLocked;
};
