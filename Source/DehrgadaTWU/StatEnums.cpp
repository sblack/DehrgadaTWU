#include "DehrgadaTWU.h"
#include "StatEnums.h"

UEnum* StatEnums::AttributesPtr;
UEnum* StatEnums::VitalsPtr;
UEnum* StatEnums::DamagePtr;

UEnum* StatEnums::Attributes()
{
	if (AttributesPtr == nullptr)
	{
		AttributesPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAttributes"), true);
	}
	return AttributesPtr;
};

UEnum* StatEnums::Vitals()
{
	if (VitalsPtr == nullptr)
	{
		VitalsPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EVitals"), true);
	}
	return VitalsPtr;
};

UEnum* StatEnums::Damage()
{
	if (DamagePtr == nullptr)
	{
		DamagePtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EDamage"), true);
	}
	return DamagePtr;
};