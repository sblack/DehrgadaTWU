// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "CombatEffect.h"
#include "AreaOfEffect.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API AAreaOfEffect : public AStaticMeshActor
{
	GENERATED_BODY()
protected:
	TArray< TTuple<ACharacter*, float> > RecentAffected;
	void ApplyEffect(ACharacter* Character);
public:
	UPROPERTY(EditAnywhere, Instanced, Category = Default)
		TArray<UCombatEffect*> Effects;

	AAreaOfEffect(const FObjectInitializer& ObjectInitializer);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;
	
};
