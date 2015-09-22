// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "TargetableInterface.h"
#include "DehrgadaTWUCharacter.generated.h"

UCLASS(Blueprintable, Abstract)
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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bCasting;

	class USheetStats * Stats;
	class USheetTalents * Talents;
	class USheetBuffs * Buffs;

	void ApplyDamage(class UDamageData* damage, float mult, int32 add) override;
	void ApplyHeal(class UHealData* heal) override;
	void ApplyBuff(class UBuffBase* buff) override;

	UFUNCTION()
		float GetDefense(EDefenses defense) const override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetMeleeAttack(float& result) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetMagicAttack(float& result) const;
};

