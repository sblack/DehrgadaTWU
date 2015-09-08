// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include "FCommand.h"
#include "Blueprint/UserWidget.h"
#include "CommandMenuCPP.generated.h"

/**
 * 
 */
UCLASS()
class DEHRGADATWU_API UCommandMenuCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	std::vector<FCommand*> Commands;
	
	void Prepare(FVector location);

	void Prepare(AActor* target);

	UFUNCTION(BlueprintCallable, Category = "Default")
	void Select(int32 index);
	
protected:
	
	void SetupMenu();

	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	void AddButton(const FString& name, int32 index);

	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	void Reposition(int32 count);

	UFUNCTION(BlueprintImplementableEvent, Category = "Default")
	void Close();
};
