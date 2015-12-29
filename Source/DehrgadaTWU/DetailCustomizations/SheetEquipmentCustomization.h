#pragma once

#include "SheetEquipment.h"
#include "Editor/DetailCustomizations/Private/DetailCustomizationsPrivatePCH.h"

class DEHRGADATWU_API SheetEquipmentCustomization : public IDetailCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<IDetailCustomization> MakeInstance();

	/** IDetailCustomization interface */
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;
};

