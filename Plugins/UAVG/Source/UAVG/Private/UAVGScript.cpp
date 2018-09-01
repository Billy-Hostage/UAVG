//NTRHostage Coded

#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"

UUAVGScript::UUAVGScript()
{
	ScriptName = FName("UAVGScript");
}

UUAVGScriptRuntimeNodeRoot* UUAVGScript::SetupNewRuntimeRootNode()
{
	RootNode = NewObject<UUAVGScriptRuntimeNodeRoot>(this, UUAVGScriptRuntimeNodeRoot::StaticClass(), NAME_None, RF_Transactional);
	AllNodes.Add(RootNode);
	return RootNode;
}

void UUAVGScript::ClearNode()
{
	RootNode = nullptr;
	AllNodes.Empty();
}
