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

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bAttacking;
};

