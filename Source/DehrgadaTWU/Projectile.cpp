// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "TalentActive.h"
#include "TalentManagerCPP.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bHome = false;

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bHome)
	{
		if (Target)
		{
			FVector diff = Target->Location() + Offset - GetActorLocation();
			float mag = diff.Size();
			float thresh = (bAirBurst || Success > 0) ? 50.f : 200.f;
			if (mag > thresh)
			{
				Movement->Velocity = diff/mag * Speed;
			}
			else
			{
				ImpactTarget();
			}
		}
		else
		{
			Cast<UPrimitiveComponent>(GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			bHome = false;
		}
	}
}

void AProjectile::SetTarget(TScriptInterface<ITargetableInterface> target, float success)
{
	//if (!target)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("WHAT THE FUCK"));
	//	return;
	//}
	//else
	//{
	//	//UE_LOG(LogTemp, Log, TEXT("%s"), *target->_getUObject()->GetName());
	//	UE_LOG(LogTemp, Log, TEXT("%s"), *target->AsActor()->GetName());
	//	return;
	//}

	Success = success;
	if (bLobbed)
	{
		Target = target;
		float roughTimeToTarget = (Target->Location() - GetActorLocation()).Size() / Speed;
		TargetPoint = Target->Location() +Target->AsActor()->GetVelocity() * roughTimeToTarget - FVector(0,0,90);
		Cast<UPrimitiveComponent>(GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		DrawDebugPoint(GetWorld(), TargetPoint, 25.f, FColor::Red, false, 1.f);

		CalculateTrajectory();
	}
	else
	{
		Target = target;
		bHome = true;
		//don't collide with anything before target
		Cast<UPrimitiveComponent>(GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (success == 0)
		{
			Offset = FMath::VRand() * 100.f + FVector(0,0,100);
		}
		else if (success == 1)
		{
			Offset = FMath::VRand() * 25.f; //some variance, but not enough to miss
		}
		else //crit
		{
			Offset = FVector::ZeroVector;
		}

		Movement->Velocity = Target->Location() + Offset - GetActorLocation();
		Movement->InitialSpeed = Speed;
	}
}

void AProjectile::SetTargetPoint(FVector point)
{
	TargetPoint = point;
	Cast<UPrimitiveComponent>(GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	CalculateTrajectory();
}

void AProjectile::CalculateTrajectory()
{
	FVector diff = TargetPoint - GetActorLocation();
	float grav = -(GetWorld()->GetDefaultGravityZ()*Movement->ProjectileGravityScale);
	if (grav != 0.f)
	{
		float tarXY = diff.Size2D();
		float angXY = FMath::Atan2(diff.Y, diff.X);
		float minSpeed = FMath::Sqrt((grav*tarXY*tarXY) / (tarXY - diff.Z));
		float angZ;
		if (Speed < minSpeed)
		{
			Movement->InitialSpeed = minSpeed;
			angZ = PI / 4.f;
		}
		else
		{
			Movement->InitialSpeed = Speed;
			angZ = FMath::Atan((Speed*Speed - FMath::Sqrt(FMath::Pow(Speed, 4) - grav*(grav*tarXY*tarXY + 2 * diff.Z*Speed*Speed))) / (grav*tarXY));
		}

		Movement->Velocity = Movement->InitialSpeed * FVector(FMath::Cos(angZ)*FMath::Cos(angXY), FMath::Cos(angZ)*FMath::Sin(angXY), FMath::Sin(angZ));
		Movement->Velocity.Y -= grav * GetWorld()->DeltaTimeSeconds / 2.f; //half a frame of acceleration for math reasons
	}
	else
	{
		Movement->Velocity = diff;
		Movement->InitialSpeed = Speed;
	}
}

void AProjectile::ImpactTarget()
{
	if (Success > 0)
	{
		//DO DAMAGE
		Terminate();
	}
	else if (bAirBurst)
	{
		Terminate();
	}
	else
	{
		Cast<UPrimitiveComponent>(GetRootComponent())->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		bHome = false;
	}
}

void AProjectile::NotifyHit(class UPrimitiveComponent * MyComp, AActor * Other, class UPrimitiveComponent * OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("NotifyHit"));
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, Other->GetName());
	Terminate();
}

void AProjectile::Terminate()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Terminate"));

	if (Talent != nullptr)
	{
		if (User != nullptr)
		{
			if (Talent->bCanTargetActor && Target && Success > 0)
			{
				ATalentManagerCPP::Instance->Use_Target(Talent, User, Target);
			}
			else if (Talent->bCanTargetLocation)
			{
				ATalentManagerCPP::Instance->Use_Location(Talent, User, GetActorLocation());
			}
		}
	}

	Destroy();
}