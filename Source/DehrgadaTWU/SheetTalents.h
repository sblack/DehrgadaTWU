// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SheetTalents.generated.h"

USTRUCT(BlueprintType)
struct DEHRGADATWU_API FModalTuple
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTalentModal* Talent;

	UPROPERTY(BlueprintReadWrite)
		bool Active;

	UPROPERTY(BlueprintReadWrite)
	class AAreaOfEffect* Aura;
};

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEHRGADATWU_API USheetTalents : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USheetTalents();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	//virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintReadWrite)
	class ADehrgadaTWUCharacter* Character;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<class UTalentActive*> ActiveTalents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<FModalTuple> ModalTalents;

	void ActDeactModal(UTalentModal* talent, bool activate);
};
