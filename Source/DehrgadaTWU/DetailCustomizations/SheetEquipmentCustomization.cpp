
#include "DehrgadaTWU.h"
#include "SheetEquipmentCustomization.h"

#define LOCTEXT_NAMESPACE "SheetStatsCustomization"

TSharedRef<IDetailCustomization> SheetEquipmentCustomization::MakeInstance()
{
	return MakeShareable(new SheetEquipmentCustomization);
}

void SheetEquipmentCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Slots", FText::GetEmpty(), ECategoryPriority::Important);

	//You can get properties using the detailbuilder
	TSharedRef<IPropertyHandle> BaseHandle = DetailBuilder.GetProperty("Equipment");

	if (!BaseHandle->IsValidHandle())
	{
		Category.AddCustomRow(LOCTEXT("Fail", "Fail"))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Fail", "Fail"))
			.Font(IDetailLayoutBuilder::GetDetailFont())
			];
		return;
	}

	BaseHandle->MarkHiddenByCustomization();

	uint32 num;
	BaseHandle->AsArray()->GetNumElements(num);
	for (uint32 i = 0; i < num; i++)
	{
		FText text = StatEnums::EquipSlots()->GetEnumText(i);
		Category.AddCustomRow(text)
			.NameContent()
			[
				SNew(STextBlock)
				.Text(text)
			.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent().MinDesiredWidth(500)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
			[
				SNew(SProperty, BaseHandle->AsArray()->GetElement(i)->GetChildHandle("Item"))
				.ShouldDisplayName(false)
			]];
	}
}

#undef LOCTEXT_NAMESPACE