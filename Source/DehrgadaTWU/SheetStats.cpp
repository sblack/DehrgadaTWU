// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"


// Sets default values for this component's properties
USheetStats::USheetStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

	for (int i = 0; i < StatEnums::Attributes()->GetMaxEnumValue(); i++)
	{
		Attributes.Add(5);
		AttributesTotal.Add(0);
		AttributesBuff.Add(0);
	}

	for (int i = 0; i < StatEnums::Vitals()->GetMaxEnumValue(); i++)
	{
		Vitals.Add(0);
		VitalsTotal.Add(0);
		VitalsBuff.Add(0);
		VitalsCurrent.Add(1);
	}

	AP = 4;
	APTotal = 4;
	APBuff = 0;
	APCurrent = 0;

	//No resistance/weakness against Typeless
	for (int i = 0; i < StatEnums::Damage()->GetMaxEnumValue() - 1; i++)
	{
		Resists.Add(0);
		ResistsTotal.Add(0);
		ResistsBuff.Add(0);
	}

	for (int i = 0; i < StatEnums::Defenses()->GetMaxEnumValue(); i++)
	{
		Defenses.Add(0);
		DefensesTotal.Add(0);
		DefensesBuff.Add(0);
	}
}


// Called when the game starts
void USheetStats::BeginPlay()
{
	Super::BeginPlay();

	UpdateTotals();

	for (int i = 0; i < VitalsCurrent.Num(); i++)
	{
		VitalsCurrent[i] = VitalsTotal[i];
	}

	// ...
	
}


// Called every frame
//void USheetStats::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
//{
//	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
//
//	// ...
//}

FReply USheetStats::UpdateFromDetailPanel()
{
	//UE_LOG(LogTemp, Log, TEXT("Button Clicked!"));
	//UE_LOG(LogTemp, Log, TEXT("%s  Attributes.Num() = %d"), *GetName(), Attributes.Num());
	//Attributes[0] += 1;
	UpdateTotals();
	return FReply::Handled();

}

//no UpdateAttributes, because Attributes affect everything anyway
void USheetStats::UpdateTotals()
{
	for (int i = 0; i < Attributes.Num(); i++)
	{
		AttributesTotal[i] = Attributes[i] + AttributesBuff[i];
	}

	UpdateVitals();
	UpdateResists();
	UpdateDefenses();
}

void USheetStats::UpdateVitals()
{
	VitalsTotal[(int)EVitals::Health] = Vitals[(int)EVitals::Health] + VitalsBuff[(int)EVitals::Health] + AttributesTotal[(int)EAttributes::Strength] + 5 * AttributesTotal[(int)EAttributes::Vitality];
	VitalsTotal[(int)EVitals::Clarity] = Vitals[(int)EVitals::Clarity] + VitalsBuff[(int)EVitals::Clarity] + 2 * AttributesTotal[(int)EAttributes::Intellect] + 4 * AttributesTotal[(int)EAttributes::Focus];
	VitalsTotal[(int)EVitals::Stamina] = Vitals[(int)EVitals::Stamina] + VitalsBuff[(int)EVitals::Stamina] + 3 * AttributesTotal[(int)EAttributes::Dexterity] + 3 * AttributesTotal[(int)EAttributes::Vitality];
	APTotal = AP + APBuff + .15f * (float)(AttributesTotal[(int)EAttributes::Dexterity]) + .075f * (float)(AttributesTotal[(int)EAttributes::Focus]);

	CheckVitals();
}

void USheetStats::UpdateResists()
{
	for (int i = 0; i < Resists.Num(); i++)
	{
		ResistsTotal[i] = Resists[i] + ResistsBuff[i] + AttributesTotal[(int)EAttributes::Vitality] * .01f;
	}
}

void USheetStats::UpdateDefenses()
{
	DefensesTotal[(int)EDefenses::Reflex] = Defenses[(int)EDefenses::Reflex] + DefensesBuff[(int)EDefenses::Reflex] + .5f * AttributesTotal[(int)EAttributes::Dexterity];
	DefensesTotal[(int)EDefenses::Deflection] = Defenses[(int)EDefenses::Deflection] + DefensesBuff[(int)EDefenses::Deflection] + DefensesTotal[(int)EDefenses::Reflex];
	DefensesTotal[(int)EDefenses::Fortitude] = Defenses[(int)EDefenses::Fortitude] + DefensesBuff[(int)EDefenses::Fortitude] + .5f * AttributesTotal[(int)EAttributes::Vitality];
	DefensesTotal[(int)EDefenses::Psyche] = Defenses[(int)EDefenses::Psyche] + DefensesBuff[(int)EDefenses::Psyche] + .5f * AttributesTotal[(int)EAttributes::Focus];
}

void USheetStats::UpdateAPForNewTurn()
{
	APCurrent += APTotal;
	if (APCurrent > APTotal * 1.5f)
		APCurrent = APTotal * 1.5f;
}