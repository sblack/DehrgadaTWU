// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "DehrgadaBFL.h"

UObject* UDehrgadaBFL::CreateObject(UClass* Class)
{
	UObject * hate = NewObject<UObject>((UObject*)GetTransientPackage(), Class);
	return hate;
}


