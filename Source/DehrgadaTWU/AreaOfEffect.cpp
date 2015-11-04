// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "CombatEffectDamage.h"
#include "AreaOfEffect.h"

AAreaOfEffect::AAreaOfEffect(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(GetRootComponent());
	prim->bGenerateOverlapEvents = true;
	prim->SetCollisionProfileName("Trigger");

	bAffectsSelf = bAffectsAllies = bAffectsEnemies = bAffectsLiving = bAffectsDying = bAffectsObjects = true;
}

void AAreaOfEffect::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ITargetable targetable = ITargetableInterface::Targetable(OtherActor);
	if (targetable != nullptr)
	{
		if (!bAffectsSelf && OtherActor == SelfActor)
		{
			return;
		}
		//TODO: Allies and Enemies
		//TODO: Living and Dying
		if (!bAffectsObjects && !OtherActor->IsA<ADehrgadaTWUCharacter>())
		{
			return;
		}
		for (int i = 0; i < RecentAffected.Num(); i++)
		{
			if (RecentAffected[i].Get<0>() == targetable)
			{
				return;
			}
		}
		RecentAffected.Emplace(targetable, AWorldTimer::Instance->GetTimeSeconds() + AWorldTimer::TurnLength);
		ApplyEffect(targetable);
	}
}

void AAreaOfEffect::Tick(float DeltaSeconds)
{
	while (RecentAffected.Num() > 0)
	{
		if (RecentAffected[0].Get<1>() <= AWorldTimer::Instance->GetTimeSeconds())
		{
			ITargetable targetable = RecentAffected[0].Get<0>();
			RecentAffected.RemoveAt(0);
			if (IsOverlappingActor(targetable->AsActor()))
			{
				RecentAffected.Emplace(targetable, AWorldTimer::Instance->GetTimeSeconds() + AWorldTimer::TurnLength);
				ApplyEffect(targetable);
			}
		}
		else
		{
			break;
		}
	}
}

void AAreaOfEffect::ApplyEffect(ITargetable targetable)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Yo: %f"), AWorldTimer::Instance->GetTimeSeconds()));
	for (int i = 0; i < Effects.Num(); i++)
	{
		if (Effects[i]->AttackRoll_NoUser(targetable, 0))
		{
			Effects[i]->Apply(targetable, NULL, GetActorLocation());
		}
		else
		{
			if (Effects[i]->IsA<UCombatEffectDamage>())
			{
				UCombatEffectDamage* dam = Cast<UCombatEffectDamage>(Effects[i]);
				if (dam->bHalfOnMiss)
				{
					dam->Apply_MA(targetable, NULL, .5f, 0);
				}
			}
			break;
		}
	}
}

void AAreaOfEffect::SetAffects(bool affSelf, bool allies, bool enemies, bool living, bool dying, bool objects)
{
	bAffectsSelf = affSelf;
	bAffectsAllies = allies;
	bAffectsEnemies = enemies;
	bAffectsLiving = living;
	bAffectsDying = dying;
	bAffectsObjects = objects;
}

void AAreaOfEffect::FinishSpawning()
{
	for (int i = 0; i < RecentAffected.Num();)
	{
		ITargetable targetable = RecentAffected[i].Get<0>();
		if (!bAffectsSelf && targetable->AsActor() == SelfActor)
		{
			RecentAffected.RemoveAt(i);
			continue;
		}
		//TODO: Allies and Enemies
		//TODO: Living and Dying
		if (!bAffectsObjects && !targetable->AsActor()->IsA<ADehrgadaTWUCharacter>())
		{
			RecentAffected.RemoveAt(i);
			continue;
		}

		ApplyEffect(targetable);
		i++;
	}
}