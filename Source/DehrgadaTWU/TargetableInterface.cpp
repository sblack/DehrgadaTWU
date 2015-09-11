// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "TargetableInterface.h"

UTargetableInterface::UTargetableInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

TScriptInterface<ITargetableInterface> ITargetableInterface::Targetable(AActor* actor)
{
	auto t = Cast<ITargetableInterface>(actor);
	if (t != nullptr){
		TScriptInterface<ITargetableInterface> s = TScriptInterface<ITargetableInterface>();
		s.SetInterface(t);
		s.SetObject(actor);
		return s;
	}

	return TScriptInterface<ITargetableInterface>();
}