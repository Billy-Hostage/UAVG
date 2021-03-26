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
	ToReturn->EditorSetupScriptText(ImportedScriptString, GetCurrentFilename());

	GEditor->GetEditorSubsystem<UImportSubsystem>()->BroadcastAssetPostImport(this, ToReturn);
	return ToReturn;
}

bool UUAVGScriptTextFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	UUAVGScriptText* ScriptToReimport = Cast<UUAVGScriptText>(Obj);
	if (ScriptToReimport)
	{
		OutFilenames.Add(ScriptToReimport->SourceFilename);
		return true;
	}
	return false;
}

void UUAVGScriptTextFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	UUAVGScriptText* ScriptToReimport = Cast<UUAVGScriptText>(Obj);
	if (ScriptToReimport && ensure(NewReimportPaths.Num() == 1))
	{
		ScriptToReimport->SourceFilename = NewReimportPaths[0];
	}
}

EReimportResult::Type UUAVGScriptTextFactory::Reimport(UObject* Obj)
{
	UUAVGScriptText* ScriptToReimport = Cast<UUAVGScriptText>(Obj);

	if (!ScriptToReimport)
	{
		return EReimportResult::Failed;
	}

	if (ScriptToReimport->SourceFilename.IsEmpty() || !FPaths::FileExists(ScriptToReimport->SourceFilename))
	{
		return EReimportResult::Failed;
	}

	bool OutCanceled = false;
	if (ImportObject(ScriptToReimport->GetClass(), ScriptToReimport->GetOuter(), *ScriptToReimport->GetName(), RF_Public | RF_Standalone, ScriptToReimport->SourceFilename, nullptr, OutCanceled))
	{
		return EReimportResult::Succeeded;
	}

	return OutCanceled ? EReimportResult::Cancelled : EReimportResult::Failed;
}

int32 UUAVGScriptTextFactory::GetPriority() const
{
	return ImportPriority;
}

#undef LOCTEXT_NAMESPACE
