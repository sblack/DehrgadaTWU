// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "RollCalculatorCPP.h"

ARollCalculatorCPP* ARollCalculatorCPP::Instance;

void ARollCalculatorCPP::SetInstance()
{
	Instance = this;
}


