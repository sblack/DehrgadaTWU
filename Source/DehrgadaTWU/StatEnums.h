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

UENUM(BlueprintType)
enum class EDamage : uint8
{
	Slashing,
	Piercing,
	Crushing,
	Fire,
	Cold,
	Electric,
	Nature,
	Spirit,
	Typeless //if any more are added, this MUST remain the last
};

/**
 * Holds pointers to the various UEnums, so they don't need to be FindObject()ed every time.
 */
class DEHRGADATWU_API StatEnums
{
private:
	static UEnum* AttributesPtr;
	static UEnum* VitalsPtr;
	static UEnum* DamagePtr;
public:
	static UEnum* Attributes();
	static UEnum* Vitals();
	static UEnum* Damage();
};