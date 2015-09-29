#pragma once
#include "InitiativeObjectInterface.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class DEHRGADATWU_API UInitiativeObjectInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class DEHRGADATWU_API IInitiativeObjectInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	//returns the new initiative value
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual float RecalculateInitiative() { return GetInitiative(); }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual float GetInitiative() const { return 0; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void StartTurn() {}

	static TScriptInterface<IInitiativeObjectInterface> InitiativeObject(UObject* object);
};

typedef TScriptInterface<IInitiativeObjectInterface> IInitiativeObject;
