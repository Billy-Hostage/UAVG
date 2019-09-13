//NTRHostage

#include "UAVGScriptText.h"

UUAVGScriptText::UUAVGScriptText()
{

}

#ifdef WITH_EDITOR
void UUAVGScriptText::EditorSetupScriptText(const FString& ScriptString)
{
	ScriptString.ParseIntoArrayLines(ScriptLines);
}
#endif
