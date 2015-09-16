// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCommand.h"
#include "TalentActive.h"
#include "FCommandTalentActive.generated.h"

/**
 * 
 */
USTRUCT()
struct DEHRGADATWU_API FCommandTalentActive : public FCommand
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		UTalentActive* Talent;

	FCommandTalentActive();
	FCommandTalentActive(UTalentActive* talent);
	FCommandTalentActive(UTalentActive* talent, ITargetable target);
	FCommandTalentActive(UTalentActive* talent, FVector location);
	~FCommandTalentActive();
};
