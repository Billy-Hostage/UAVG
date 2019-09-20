//NTRHostage

#include "UAVGScriptText.h"
#include "Internationalization/StringTable.h"

UUAVGScriptText::UUAVGScriptText()
{

}

TArray<FString> UUAVGScriptText::GetLocalizedScriptLines()
{
	TArray<FString> LocalizedScriptTextLine;

	for (const FText& txt : ScriptLines)
	{
		//Preprocess stringtables, etc.
		LocalizedScriptTextLine.Add(txt.ToString());
	}

	return LocalizedScriptTextLine;
}

#ifdef WITH_EDITOR
void UUAVGScriptText::EditorSetupScriptText(const FString& ScriptString)
{
	TArray<FString> StrScriptLines;
	ScriptString.ParseIntoArrayLines(StrScriptLines, true);//Culled out all empty lines here

	for (const FString& str : StrScriptLines)
	{
		ScriptLines.Add(FText::FromString(str));
	}
}
#endif
