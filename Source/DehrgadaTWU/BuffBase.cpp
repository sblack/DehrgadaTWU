// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "BuffBase.h"

FBuffTimer::FBuffTimer(UBuffBase* buff, float timeNow)
{
	Buff = buff;
	NextTime = timeNow + AWorldTimer::TurnLength;
	TurnsLeft = buff->Duration;
}

