//NTRHostage

#include "UAVGScriptText.h"

UUAVGScriptText::UUAVGScriptText()
{

}

const TArray<FString>& UUAVGScriptText::GetLocalizedScriptLines()
{
	if (LocalizedScriptTextLine.Num() != ScriptLines.Num())
	{
		LocalizedScriptTextLine.Empty();
		for (const FText& txt : ScriptLines)
		{
			LocalizedScriptTextLine.Add(txt.ToString());
		}
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
