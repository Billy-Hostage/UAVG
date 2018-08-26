//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UAVGScriptFactory.generated.h"

UCLASS()
class UUAVGScriptFactory : public UFactory
{
	GENERATED_BODY()
public:
	UUAVGScriptFactory();
 
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// End of UFactory interface
};