// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "SheetTalents.h"
#include "PCControllerSlave.h"
#include "FCommandTalentModal.h"

FCommandTalentModal::FCommandTalentModal() : FCommand()
{
	Name = FText::FromString("Talent");
	bNoMove = true;
}

FCommandTalentModal::FCommandTalentModal(UTalentModal* talent, bool activate) : FCommand()
{
	Name = talent->Name;
	Talent = talent;
	bActivate = activate;
	bNoMove = true;
}

FCommandTalentModal::~FCommandTalentModal()
{
}

bool FCommandTalentModal::CanUse(ADehrgadaTWUCharacter* user)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This far?"));
	bool hasTalent = false;
	for (int i = 0; i < user->Talents->ModalTalents.Num(); i++)
	{
		if (user->Talents->ModalTalents[i].Talent == Talent)
		{
			if (user->Talents->ModalTalents[i].Active == bActivate)
			{
				if (bActivate)
				{
					UE_LOG(LogTemp, Log, TEXT("Modal Talent already active"));
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Modal Talent already inactive"));
				}
				return false;
			}
			hasTalent = true;
			break;
		}
	}
	if (!hasTalent)
	{
		UE_LOG(LogTemp, Log, TEXT("user does not have modal talent"));
		return false;
	}

	if (bActivate)
	{
		for (int i = 0; i < StatEnums::Vitals()->GetMaxEnumValue(); i++)
		{
			if (user->Stats->VitalsCurrent[i] < Talent->VitalCost((EVitals)i))
				return false;
		}
	}

	return FCommand::CanUse(user);
}

void FCommandTalentModal::Perform()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, TEXT("Perform Modal"));
	Resolve();
}

void FCommandTalentModal::Resolve()
{
	Performer->GetDehrgadaTWUCharacter()->Talents->ActDeactModal(Talent, bActivate);
}
