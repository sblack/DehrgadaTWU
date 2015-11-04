// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TargetableForBP.generated.h"

UCLASS(Blueprintable, Abstract)
class DEHRGADATWU_API ATargetableForBP : public AActor, public ITargetableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetableForBP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Target")
	void ApplyDamage(class UDamageData* damage, float mult, int32 add) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Target")
	void ApplyHeal(class UHealData* heal) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Target")
	void ApplyBuff(class UBuffBase* buff) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Target")
	void RemoveBuff(class UBuffBase* buff) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Target")
		float GetDefense(EDefenses defense) const override;
	
};
