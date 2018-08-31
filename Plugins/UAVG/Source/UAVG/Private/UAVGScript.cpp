//NTRHostage Coded

#include "UAVGScript.h"
#include "UAVGScriptRTNode.h"
#ifdef WITH_EDITORONLY_DATA
#include "UAVGEditor/Public/UAVGScriptGraph/Nodes/UAVGScriptGraphNodeRoot.h"
#endif

UUAVGScript::UUAVGScript()
{
	ScriptName = FName("UAVGScript");
}

void UUAVGScript::SetRuntimeRootNode(UUAVGScriptGraphNodeRoot* InGNode)
{
	check(InGNode);

	RootNode = NewObject<UUAVGScriptRuntimeNodeRoot>(this, UUAVGScriptRuntimeNodeRoot::StaticClass(), NAME_None, RF_Transactional);
	AllNodes.Add(RootNode);
	InGNode->MyRTNode = RootNode;
}

void UUAVGScript::ClearNode()
{
	RootNode = nullptr;
	AllNodes.Empty();
}
