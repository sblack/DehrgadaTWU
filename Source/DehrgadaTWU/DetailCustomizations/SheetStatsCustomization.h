// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SheetStats.h"
#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"

/**
 * 
 */
class DEHRGADATWU_API SheetStatsCustomization : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	void StatDetails(IDetailLayoutBuilder& DetailBuilder, FString StatName, UEnum* EnumPtr);
	void VitalDetails(IDetailLayoutBuilder& DetailBuilder);
	void UpdateButton(IDetailLayoutBuilder& DetailBuilder);
};
