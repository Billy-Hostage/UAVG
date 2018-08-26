//NTRHostage Coded

#include "UAVGScriptFactory.h"
#include "UAVGScript.h"

#define LOCTEXT_NAMESPACE "UAVGScript"

UUAVGScriptFactory::UUAVGScriptFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UUAVGScript::StaticClass();
}

UObject* UUAVGScriptFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UObject* NewAsset = NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
	//TODO Setup Default Value
	return NewAsset;
}

#undef LOCTEXT_NAMESPACE