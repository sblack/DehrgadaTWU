// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "DehrgadaTWUCharacter.generated.h"

UCLASS(Blueprintable)
class ADehrgadaTWUCharacter : public ACharacter
{
	GENERATED_BODY()


public:
	ADehrgadaTWUCharacter();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bDying;

	class USheetStats * Stats;
};

