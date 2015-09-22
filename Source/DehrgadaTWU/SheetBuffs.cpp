// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "SheetStats.h"
#include "SheetBuffs.h"


// Sets default values for this component's properties
USheetBuffs::USheetBuffs(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USheetBuffs::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USheetBuffs::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	while (Durational.Num() > 0)
	{
		if (AWorldTimer::Instance->GetTimeSeconds() > Durational[0]->NextTime)
		{
			FBuffTimer* timer = Durational[0];
			Durational.RemoveAt(0);
			timer->TurnsLeft--;
			if (timer->TurnsLeft < 1)
			{
				RemoveBuff(timer->Buff, true);
			}
			else
			{
				timer->NextTime += AWorldTimer::TurnLength;
				Durational.Add(timer);
			}
		}
		else
		{
			break;
		}
	}
}

void USheetBuffs::ApplyBuff(UBuffBase* buff)
{
	if (buff->Duration > 0)
	{
		FBuffTimer* timer = new FBuffTimer(buff, AWorldTimer::Instance->GetTimeSeconds());
		Durational.Add(timer);
	}
	else
	{
		Persistant.Add(buff);
	}

	ApplyRemoveBuffEffects(buff, true);
}

void USheetBuffs::RemoveBuff(UBuffBase* buff, bool fromTick)
{
	if (buff->Duration == 0)
	{
		bool found = false;
		for (int i = 0; i < Persistant.Num(); i++)
		{
			if (Persistant[i] == buff)
			{
				found = true;
				Persistant.RemoveAt(i);
			}
		}
		if (!found)
		{
			UE_LOG(LogDehrgadaTWU, Warning, TEXT("Tried to remove buff that wasn't there. %s"), *Character->GetName());
			return;
		}
	}
	else if (!fromTick)
	{
		bool found = false;
		for (int i = 0; i < Durational.Num(); i++)
		{
			if (Durational[i]->Buff == buff)
			{
				found = true;
				Durational.RemoveAt(i);
			}
		}
		if (!found)
		{
			UE_LOG(LogDehrgadaTWU, Warning, TEXT("Tried to remove buff that wasn't there. %s"), *Character->GetName());
			return;
		}
	}

	ApplyRemoveBuffEffects(buff, false);
}

void USheetBuffs::ApplyRemoveBuffEffects(UBuffBase* buff, bool applyEffect)
{
	float mult = (applyEffect) ? 1.f : -1.f;
	if (buff->IsA<UBuffVital>())
	{
		UBuffVital* vital = Cast<UBuffVital>(buff);
		Character->Stats->VitalsBuff[(int)vital->Vital] += vital->Amount * mult;
		Character->Stats->UpdateVitals();
	}
	else if (buff->IsA<UBuffAttribute>())
	{
		UBuffAttribute* attri = Cast<UBuffAttribute>(buff);
		Character->Stats->AttributesBuff[(int)attri->Attribute] += attri->Amount * mult;
		Character->Stats->UpdateTotals();
	}
	else if (buff->IsA<UBuffResist>())
	{
		UBuffResist* resist = Cast<UBuffResist>(buff);
		if (resist->Resist != EDamage::Typeless)
		{
			Character->Stats->ResistsBuff[(int)resist->Resist] += resist->Amount * mult;
			Character->Stats->UpdateResists();
		}
	}
	else if (buff->IsA<UBuffDefense>())
	{
		UBuffDefense* defense = Cast<UBuffDefense>(buff);
		Character->Stats->DefensesBuff[(int)defense->Defense] += defense->Amount * mult;
		Character->Stats->UpdateDefenses();
	}
}
