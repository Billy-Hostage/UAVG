//NTRHostage

#include "UAVGTextScriptInterpreter.h"
#include "UAVGScriptText.h"

UUAVGTextScriptInterpreter::UUAVGTextScriptInterpreter()
{

}

void UUAVGTextScriptInterpreter::SetupInterpreter(class UUAVGScriptText* InScriptTextAsset)
{
	if (!ensure(InScriptTextAsset))
		return;

	ScriptTextAsset = InScriptTextAsset;
	TextLinePointer = 0;
}

void UUAVGTextScriptInterpreter::OnArrive(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	if (IsScriptTextCompleted())
	{
		//This should never happen!
		Response.NodeType = EUAVGRuntimeNodeType::URNT_MAX;
		return;
	}
	
	TCHAR CurrentLineCommand = ScriptTextAsset->GetLocalizedScriptLines()[TextLinePointer][0];
	switch (CurrentLineCommand)//Command Switch
	{
	case '!'://Trigger events
		break;

	case '@'://Add Env Descriptor
		break;
	case '%'://Remove Env Descriptor
		break;

	//case '*'://Tagging is not implemented yet!
	//	break;

	case '\''://Works the same as default
	default://say command as normal
		break;
	}
}

bool UUAVGTextScriptInterpreter::IsScriptTextCompleted()
{
	return ScriptTextAsset == nullptr || !ScriptTextAsset->GetLocalizedScriptLines().IsValidIndex(TextLinePointer);
}