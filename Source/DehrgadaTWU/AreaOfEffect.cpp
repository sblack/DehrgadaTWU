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
}

void AAreaOfEffect::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA<ACharacter>())
	{
		ACharacter* character = Cast<ACharacter>(OtherActor);
		for (int i = 0; i < RecentAffected.Num(); i++)
		{
			if (RecentAffected[i].Get<0>() == character)
			{
				return;
			}
		}
		RecentAffected.Emplace(character, AWorldTimer::Instance->GetTimeSeconds() + AWorldTimer::TurnLength);
		ApplyEffect(character);
	}
}

void AAreaOfEffect::Tick(float DeltaSeconds)
{
	while (RecentAffected.Num() > 0)
	{
		if (RecentAffected[0].Get<1>() <= AWorldTimer::Instance->GetTimeSeconds())
		{
			ACharacter* character = RecentAffected[0].Get<0>();
			RecentAffected.RemoveAt(0);
			if (IsOverlappingActor(character))
			{
				RecentAffected.Emplace(character, AWorldTimer::Instance->GetTimeSeconds() + AWorldTimer::TurnLength);
				ApplyEffect(character);
			}
		}
		else
		{
			break;
		}
	}
}

void AAreaOfEffect::ApplyEffect(ACharacter* Character)
{
	TScriptInterface<ITargetableInterface> target = ITargetableInterface::Targetable(Character);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Yo: %f"), AWorldTimer::Instance->GetTimeSeconds()));
	for (int i = 0; i < Effects.Num(); i++)
	{
		if (Effects[i]->AttackRoll_NoUser(target, 0))
		{
			Effects[i]->Apply(target, NULL, GetActorLocation());
		}
		else
		{
			if (Effects[i]->IsA<UCombatEffectDamage>())
			{
				UCombatEffectDamage* dam = Cast<UCombatEffectDamage>(Effects[i]);
				if (dam->bHalfOnMiss)
				{
					dam->Apply_MA(target, NULL, .5f, 0);
				}
			}
			break;
		}
	}
}


