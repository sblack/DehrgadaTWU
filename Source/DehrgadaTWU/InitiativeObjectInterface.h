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
protected:
	bool bIsMyTurn = true;
public:
	//returns the new initiative value
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual float RecalculateInitiative() { return GetInitiative(); }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual float GetInitiative() const { return 0; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void StartTurn() {}
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual void SetIsMyTurn(bool isMyTurn) { bIsMyTurn = isMyTurn; }
	UFUNCTION(BlueprintCallable, Category = "Combat")
		virtual bool GetIsMyTurn() const { return bIsMyTurn; }

	static TScriptInterface<IInitiativeObjectInterface> InitiativeObject(UObject* object);
};

typedef TScriptInterface<IInitiativeObjectInterface> IInitiativeObject;
