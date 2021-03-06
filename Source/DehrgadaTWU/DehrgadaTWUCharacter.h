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

	UFUNCTION(BlueprintPure, Category = "Utilities|Transformation")
	FVector GetFeetLocation() const { return GetCharacterMovement()->GetActorFeetLocation(); }

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bCancel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bAttacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bDying;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimTriggers")
		bool bCasting;

	UPROPERTY(BlueprintReadOnly)
	class USheetStats * Stats;

	UPROPERTY(BlueprintReadOnly)
	class USheetTalents * Talents;

	UPROPERTY(BlueprintReadOnly)
	class USheetBuffs * Buffs;

	UPROPERTY(BlueprintReadOnly)
	class USheetEquipment * Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent * LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent * RightHand;

	void ApplyDamage(class UDamageData* damage, float mult, int32 add) override;
	void ApplyHeal(class UHealData* heal) override;
	void ApplyBuff(class UBuffBase* buff) override;
	void RemoveBuff(class UBuffBase* buff) override;

	UFUNCTION()
		float GetDefense(EDefenses defense) const override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetMeleeAttack(float& result) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetRangedAttack(float& result) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetMagicAttack(float& result) const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Combat")
		void GetFalloffModifier(float& result) const;
};

