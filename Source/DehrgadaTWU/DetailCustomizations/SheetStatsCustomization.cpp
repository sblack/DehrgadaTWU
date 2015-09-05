// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "SheetStats.h"
#include "SheetStatsCustomization.h"

#define LOCTEXT_NAMESPACE "SheetStatsCustomization"

TSharedRef<IDetailCustomization> SheetStatsCustomization::MakeInstance()
{
	return MakeShareable(new SheetStatsCustomization);
}

void SheetStatsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	UpdateButton(DetailBuilder);
	StatDetails(DetailBuilder, TEXT("Attributes"), StatEnums::Attributes());
	StatDetails(DetailBuilder, TEXT("Vitals"), StatEnums::Vitals());
}

void SheetStatsCustomization::UpdateButton(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory("Update", FText::GetEmpty(), ECategoryPriority::Important);

	TArray< TWeakObjectPtr<UObject> > objects;

	DetailBuilder.GetObjectsBeingCustomized(objects);

	if (!objects[0].IsValid())
	{

		Category.AddCustomRow(LOCTEXT("Fail", "Fail"))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Fail", "Fail"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			]
		.ValueContent().MinDesiredWidth(500)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("ButtonFail", "Could not get USheetStats"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			];
		return;
	}
	else
	{
		USheetStats* sheet = Cast<USheetStats>(objects[0].Get());
		if (sheet != nullptr)
		{
			Category.AddCustomRow(LOCTEXT("Success", "Success"))
				.NameContent()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("Update", "Update"))
					.Font(IDetailLayoutBuilder::GetDetailFont())
				]
			.ValueContent().MinDesiredWidth(500)
				[
					SNew(SButton)
					.Text(LOCTEXT("Update", "Update"))
					.OnClicked_UObject(sheet, &USheetStats::UpdateFromDetailPanel)
				];
		}
	}
}

void SheetStatsCustomization::StatDetails(IDetailLayoutBuilder& DetailBuilder, FString StatName, UEnum* EnumPtr)
{
	IDetailCategoryBuilder& Category = DetailBuilder.EditCategory(FName(*StatName), FText::FromString(StatName), ECategoryPriority::Important);

	//You can get properties using the detailbuilder
	TSharedRef<IPropertyHandle> BaseHandle = DetailBuilder.GetProperty(FName(*StatName));
	TSharedRef<IPropertyHandle> TotalHandle = DetailBuilder.GetProperty(FName(*(StatName+"Total")));

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
	if (!TotalHandle->IsValidHandle())
	{
		Category.AddCustomRow(LOCTEXT("Fail2", "Fail Total"))
			.NameContent()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Fail2", "Fail Total"))
				.Font(IDetailLayoutBuilder::GetDetailFont())
			];

		return;
	}

	BaseHandle->MarkHiddenByCustomization();
	TotalHandle->MarkHiddenByCustomization();

	uint32 num;
	BaseHandle->AsArray()->GetNumElements(num);
	for (uint32 i = 0; i < num; i++)
	{
		FText text = EnumPtr->GetEnumText(i);
		FText total;
		TotalHandle->AsArray()->GetElement(i)->GetValueAsDisplayText(total);
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
					SNew(SProperty, BaseHandle->AsArray()->GetElement(i))
					.ShouldDisplayName(false)
				]
				+ SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(total)
					.Font(IDetailLayoutBuilder::GetDetailFont())
					.Justification(ETextJustify::Center)
				]
			];
	}
}

#undef LOCTEXT_NAMESPACE
