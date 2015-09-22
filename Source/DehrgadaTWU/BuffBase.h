// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "StatEnums.h"
#include "BuffBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, EditInlineNew, BlueprintType)
class DEHRGADATWU_API UBuffBase : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
		int32 Amount;
	//in rounds (5sec). 0 = non-durational
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0), Category = Buff)
		int32 Duration;
};

UCLASS()
class DEHRGADATWU_API UBuffVital : public UBuffBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
		EVitals Vital;
};

UCLASS()
class DEHRGADATWU_API UBuffAttribute : public UBuffBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
		EAttributes Attribute;
};

UCLASS()
class DEHRGADATWU_API UBuffDefense : public UBuffBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
		EDefenses Defense;
};

UCLASS()
class DEHRGADATWU_API UBuffResist : public UBuffBase
{
	GENERATED_BODY()
public:
	//Buffs to Typeless resistance will be IGNORED. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buff)
		EDamage Resist;
};

struct FBuffTimer
{
	UBuffBase* Buff;
	float NextTime;
	int32 TurnsLeft;

	FBuffTimer(UBuffBase* buff, float timeNow);
};