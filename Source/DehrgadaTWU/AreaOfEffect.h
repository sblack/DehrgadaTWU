// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMeshActor.h"
#include "AreaOfEffect.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API AAreaOfEffect : public AStaticMeshActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsSelf;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsAllies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsLiving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsDying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAffectsObjects;

	TArray< TTuple<ITargetable, float> > RecentAffected;
	void ApplyEffect(ITargetable targetable);
public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = Default)
		TArray<class UCombatEffect*> Effects;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = Default)
		TArray<class UAttackRoll*> AttackRolls;

	//the "Self" for purposes of who/what is affected
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		AActor* SelfActor; 

	AAreaOfEffect(const FObjectInitializer& ObjectInitializer);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;
	
	//if this is for an AOE from a talent, use Talents/SetupAreaOfEffect instead
	UFUNCTION(BlueprintCallable, Category = "AOE")
		void SetAffects(bool affSelf, bool allies, bool enemies, bool living, bool dying, bool objects);

	//because UE4 Actors are so fucking impatient, gotta check physics RIGHT NOW NO WAITING
	UFUNCTION(BlueprintCallable, Category = "AOE")
		void FinishSpawning();
};
