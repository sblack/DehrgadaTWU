#include "DehrgadaTWU.h"
#include "InitiativeObjectInterface.h"

UInitiativeObjectInterface::UInitiativeObjectInterface(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

TScriptInterface<IInitiativeObjectInterface> IInitiativeObjectInterface::InitiativeObject(UObject* object)
{
	auto t = Cast<IInitiativeObjectInterface>(object);
	if (t != nullptr){
		TScriptInterface<IInitiativeObjectInterface> s = TScriptInterface<IInitiativeObjectInterface>();
		s.SetInterface(t);
		s.SetObject(object);
		return s;
	}

	return TScriptInterface<IInitiativeObjectInterface>();
}