// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS(Blueprintable)
class DEHRGADATWU_API AProjectile : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* Movement;

	//if true, projectile arcs and does NOT home.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bLobbed;
	//if true, missed shots "detonate" near target rather than overshooting. Only applicable to targetted shots.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bAirBurst;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ClampMin = 0))
		float Speed;

	bool bHome;

	FVector TargetPoint;
	ITargetable Target;
	float Success; // 0 = miss, 1 = hit, >1 = crit mult
	FTimerHandle TimerHandle_Impact;
	FVector Offset;

	class UTalentActive* Talent;
	class ADehrgadaTWUCharacter* User;

	void CalculateTrajectory();
	void ImpactTarget();
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void SetUser(class ADehrgadaTWUCharacter* user) { User = user; }

	//success: 0 = miss, 1 = hit, >1 = crit mult
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void SetTarget(TScriptInterface<ITargetableInterface> target, float success);
	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void SetTargetPoint(FVector point);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
		void SetTalent(class UTalentActive* talent) { Talent = talent; }

	void NotifyHit(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit) override;

	void Terminate();
};
