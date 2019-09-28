//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UAVGScriptTextFactory.generated.h"

UCLASS()
class UUAVGScriptTextFactory : public UFactory
{
	GENERATED_BODY()
public:
	UUAVGScriptTextFactory();

protected:
	virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;
};