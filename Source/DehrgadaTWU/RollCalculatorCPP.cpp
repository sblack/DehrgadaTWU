// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"

URollCalculatorCPP* URollCalculatorCPP::Instance;

void URollCalculatorCPP::SetInstance()
{
	Instance = this;
}


