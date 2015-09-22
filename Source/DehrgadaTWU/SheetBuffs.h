// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DehrgadaTWUCharacter.h"
#include "BuffBase.h"
#include "SheetBuffs.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEHRGADATWU_API USheetBuffs : public UActorComponent
{
	GENERATED_BODY()
protected:
	void ApplyRemoveBuffEffects(UBuffBase* buff, bool applyEffect);

public:	
	// Sets default values for this component's properties
	USheetBuffs(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintReadOnly)
		ADehrgadaTWUCharacter* Character;
	
	TArray<UBuffBase*> Persistant;
	TArray<FBuffTimer*> Durational;

	void ApplyBuff(UBuffBase* buff);

	void RemoveBuff(UBuffBase* buff, bool fromTick = false);
};

