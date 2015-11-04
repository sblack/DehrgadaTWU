// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "TalentManagerCPP.h"
#include "TalentModal.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "CombatEffect.h"
#include "BuffBase.h"
#include "AreaOfEffect.h"
#include "SheetTalents.h"


// Sets default values for this component's properties
USheetTalents::USheetTalents()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USheetTalents::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
//void USheetTalents::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
//{
//	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
//
//	// ...
//}

void USheetTalents::ActDeactModal(UTalentModal* talent, bool activate)
{
	for (int i = 0; i < ModalTalents.Num(); i++)
	{
		if (ModalTalents[i].Talent == talent)
		{
			if (ModalTalents[i].Active == activate)
			{
				if (activate)
				{
					UE_LOG(LogTemp, Error, TEXT("Modal Talent already active"));
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Modal Talent already inactive"));
				}
				return;
			}
			if (activate)
			{
				for (int j = 0; j < StatEnums::Vitals()->GetMaxEnumValue(); j++)
				{
					Character->Stats->VitalsBuff[j] -= talent->VitalCost((EVitals)j);
				}
				Character->Stats->UpdateVitals();

				if (talent->IsA<UTalentAura>())
				{
					AAreaOfEffect* aura = nullptr;
					ATalentManagerCPP::Instance->SpawnAura(Cast<UTalentAura>(talent), Character, aura);
					ModalTalents[i].Aura = aura;
				}
				else
				{
					UCombatEffect::ApplyEffects(Character, talent->Effects, Character);
				}

				ModalTalents[i].Active = true;

				if (talent->ModalSet != "")
				{
					//run through the rest for matching ModalSets
					for (++i; i < ModalTalents.Num(); i++)
					{
						if (talent->ModalSet == ModalTalents[i].Talent->ModalSet && ModalTalents[i].Active)
						{
							for (int j = 0; j < StatEnums::Vitals()->GetMaxEnumValue(); j++)
							{
								Character->Stats->VitalsBuff[j] += ModalTalents[i].Talent->VitalCost((EVitals)j);
							}
							Character->Stats->UpdateVitals();

							if (ModalTalents[i].Aura != nullptr)
							{
								ModalTalents[i].Aura->Destroy();
								ModalTalents[i].Aura = nullptr;
							}
							else
							{
								UCombatEffect::RemoveEffects(Character, ModalTalents[i].Talent->Effects);
							}

							ModalTalents[i].Active = false;
						}
					}
				}
			}
			else //deactivate
			{
				for (int j = 0; j < StatEnums::Vitals()->GetMaxEnumValue(); j++)
				{
					Character->Stats->VitalsBuff[j] += talent->VitalCost((EVitals)j);
				}
				Character->Stats->UpdateVitals();

				if (ModalTalents[i].Aura != nullptr)
				{
					ModalTalents[i].Aura->Destroy();
					ModalTalents[i].Aura = nullptr;
				}
				else
				{
					UCombatEffect::RemoveEffects(Character, talent->Effects);
				}

				ModalTalents[i].Active = false;
			}

			return;
		}
		else if (activate && talent->ModalSet != "" && talent->ModalSet == ModalTalents[i].Talent->ModalSet && ModalTalents[i].Active)
		{
			for (int j = 0; j < StatEnums::Vitals()->GetMaxEnumValue(); j++)
			{
				Character->Stats->VitalsBuff[j] += ModalTalents[i].Talent->VitalCost((EVitals)j);
			}
			Character->Stats->UpdateVitals();

			if (ModalTalents[i].Aura != nullptr)
			{
				ModalTalents[i].Aura->Destroy();
				ModalTalents[i].Aura = nullptr;
			}
			else
			{
				UCombatEffect::RemoveEffects(Character, ModalTalents[i].Talent->Effects);
			}

			ModalTalents[i].Active = false;
		}
	}

	UE_LOG(LogTemp, Error, TEXT("Modal Talent not found"));
}