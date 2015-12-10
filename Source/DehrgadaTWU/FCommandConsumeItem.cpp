// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "ItemConsumable.h"
#include "CommandDrivenController.h"
#include "DehrgadaTWUCharacter.h"
#include "FCommandConsumeItem.h"

FCommandConsumeItem::FCommandConsumeItem() : FCommand()
{
	Name = FText::FromString("Consume");
}

FCommandConsumeItem::FCommandConsumeItem(UItemConsumable* item) : FCommand()
{
	Name = item->ActionText;
	Item = item;
	BaseAP = 4;
	bNoMove = true;
}

//TODO: trigger animation
void FCommandConsumeItem::Perform()
{
	Resolve();
}

void FCommandConsumeItem::Resolve()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Consume!"));
	UCombatEffect::ApplyEffects(Performer->GetDehrgadaTWUCharacter(), Item->Effects, Performer->GetDehrgadaTWUCharacter());
}


