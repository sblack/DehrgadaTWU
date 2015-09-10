// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
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
		RecentAffected.Emplace(character, GetWorld()->TimeSeconds + 5.0f);
		ApplyEffect(character);
	}
}

void AAreaOfEffect::Tick(float DeltaSeconds)
{
	while (RecentAffected.Num() > 0)
	{
		if (RecentAffected[0].Get<1>() <= GetWorld()->TimeSeconds)
		{
			ACharacter* character = RecentAffected[0].Get<0>();
			RecentAffected.RemoveAt(0);
			if (IsOverlappingActor(character))
			{
				RecentAffected.Emplace(character, GetWorld()->TimeSeconds + 5.0f);
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Yo: %f"), GetWorld()->TimeSeconds));
}


