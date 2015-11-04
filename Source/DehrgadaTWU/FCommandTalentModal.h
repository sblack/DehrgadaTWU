// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FCommand.h"
#include "TalentModal.h"
#include "FCommandTalentModal.generated.h"

/**
 * 
 */
USTRUCT()
struct DEHRGADATWU_API FCommandTalentModal : public FCommand
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		UTalentModal* Talent;
	UPROPERTY(BlueprintReadOnly)
		bool bActivate;

	FCommandTalentModal();
	FCommandTalentModal(UTalentModal* talent, bool activate);
	~FCommandTalentModal();

	virtual bool CanUse(class ADehrgadaTWUCharacter* user) override;

	virtual void Perform() override;

	virtual void Resolve() override;
};
