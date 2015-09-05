#pragma once
#include "StatEnums.generated.h"


UENUM(BlueprintType)
enum class EAttributes : uint8
{
	Strength,
	Dexterity,
	Vitality,
	Intellect,
	Focus,
	Clout
};

UENUM(BlueprintType)
enum class EVitals : uint8
{
	Health,
	Clarity,
	Stamina
};

/**
 * Holds pointers to the various UEnums, so they don't need to be FindObject()ed every time.
 */
class DEHRGADATWU_API StatEnums
{
private:
	static UEnum* AttributesPtr;
	static UEnum* VitalsPtr;
public:
	static UEnum* Attributes();
	static UEnum* Vitals();
};