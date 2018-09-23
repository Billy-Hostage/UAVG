//NTRHostage Coded

#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"

UUAVGScript::UUAVGScript()
{
}

UUAVGScriptRuntimeNodeRoot* UUAVGScript::SetupNewRuntimeScript()
{
	RootNode = NewObject<UUAVGScriptRuntimeNodeRoot>(this, UUAVGScriptRuntimeNodeRoot::StaticClass(), NAME_None, RF_Transactional);
	AllNodes.Empty();
	AllNodes.Add(RootNode);
	return RootNode;
}

bool UUAVGScript::AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode)
{
	//TODO
	return true;
}
