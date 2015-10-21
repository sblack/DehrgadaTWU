// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaTWUCharacter.h"
#include "SheetStats.h"
#include "PCControllerSlave.h"
#include "TalentManagerCPP.h"
#include "RollCalculatorCPP.h"
#include "Projectile.h"
#include "FCommandTalentActive.h"

FCommandTalentActive::FCommandTalentActive() : FCommand()
{
	Name = FText::FromString("Talent");
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent) : FCommand()
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->GetProximity();
	BaseAP = talent->APCost;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, ITargetable target) : FCommand(target)
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->GetProximity();
	if (Proximity < 150) Proximity = 150;
	BaseAP = talent->APCost;
}

FCommandTalentActive::FCommandTalentActive(UTalentActive* talent, FVector location) : FCommand(location)
{
	Name = talent->Name;
	Talent = talent;
	Proximity = talent->GetProximity();
	if (Proximity < 10) Proximity = 10;
	BaseAP = talent->APCost;
}

FCommandTalentActive::~FCommandTalentActive()
{
}

bool FCommandTalentActive::CanUse(ADehrgadaTWUCharacter* user)
{
	for (int i = 0; i < StatEnums::Vitals()->GetMaxEnumValue(); i++)
	{
		if (user->Stats->VitalsCurrent[i] < Talent->VitalCost((EVitals)i))
			return false;
	}

	return FCommand::CanUse(user);
}

void FCommandTalentActive::Perform()
{
	Performer->GetDehrgadaTWUCharacter()->bCasting = true;
}

void FCommandTalentActive::Resolve()
{
	if (Talent->IsA<UTalentActiveProjectile>())
	{
		UTalentActiveProjectile* tp = Cast<UTalentActiveProjectile>(Talent);
		const FVector loca = Performer->GetPawn()->GetActorLocation();
		FActorSpawnParameters fuckyou;
		fuckyou.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AProjectile* projectile = Cast<AProjectile>(Performer->GetWorld()->SpawnActor(tp->Projectile, &loca, NULL, fuckyou));

		projectile->SetUser(Performer->GetDehrgadaTWUCharacter());
		projectile->SetTalent(Talent);
		if (Target && Talent->bCanTargetActor)
		{
			bool suc;
			ARollCalculatorCPP::Instance->RangedAttack(Target, Performer->GetDehrgadaTWUCharacter(), tp->Defense, tp->Range, tp->Falloff, suc);
			projectile->SetTarget(Target, (suc)?1:0);
		}
		else
		{
			projectile->SetTargetPoint(GetTargetLocation());
		}
	}
	else
	{
		if (Target && Talent->bCanTargetActor)
		{
			ATalentManagerCPP::Instance->Use_Target(Talent, Performer->GetDehrgadaTWUCharacter(), Target);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Target!"));
		}
		else
		{
			ATalentManagerCPP::Instance->Use_Location(Talent, Performer->GetDehrgadaTWUCharacter(), GetTargetLocation());
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Location!"));
		}
	}

	Performer->GetDehrgadaTWUCharacter()->Stats->SpendVitals(Talent);
}