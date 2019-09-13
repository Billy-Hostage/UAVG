//NTRHostage

#include "UAVGScriptTextFactory.h"
#include "UAVGScriptText.h"
#include "Editor.h"

#define LOCTEXT_NAMESPACE "UAVGScriptText"

UUAVGScriptTextFactory::UUAVGScriptTextFactory()
{
	bCreateNew = false;
	bEditAfterNew = false;
	bEditorImport = true;
	bText = true;
	SupportedClass = UUAVGScriptText::StaticClass();
	Formats.Add("us;UAVG Script File");
}

UObject* UUAVGScriptTextFactory::FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn)
{
	UUAVGScriptText* ToReturn = nullptr;
	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPreImport(this, InClass, InParent, InName, Type);

	//TODO We can pop options here.
	
	FString ImportedScriptString;
	int32 NumOfChars = (BufferEnd - Buffer);
	TArray<TCHAR>& StringChars = ImportedScriptString.GetCharArray();
	StringChars.AddUninitialized(NumOfChars + 1);
	FMemory::Memcpy(StringChars.GetData(), Buffer, NumOfChars * sizeof(TCHAR));
	StringChars.Last() = 0;
	//Complete string building

	ToReturn = NewObject<UUAVGScriptText>(InParent, InClass, InName, Flags | RF_Transactional);
	ToReturn->EditorSetupScriptText(ImportedScriptString);

	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPostImport(this, ToReturn);
	return ToReturn;
}

#undef LOCTEXT_NAMESPACE