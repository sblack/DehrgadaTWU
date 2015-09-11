// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "TargetableInterface.h"
#include "DehrgadaTWUCharacter.generated.h"

UCLASS(Blueprintable)
class ADehrgadaTWUCharacter : public ACharacter, public ITargetableInterface
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

	void ApplyDamage(class UDamageData* damage, float mult, int32 add) override;
};

