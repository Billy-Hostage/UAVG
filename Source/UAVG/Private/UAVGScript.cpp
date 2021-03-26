//NTRHostage Coded

#include "UAVGScript.h"
#include "Nodes/UAVGScriptRTNodeRoot.h"
#include "Nodes/UAVGScriptRTNodeSaySingle.h"

DEFINE_LOG_CATEGORY(LogUAVGRuntimeScript);

UUAVGScript::UUAVGScript()
{
}

UUAVGScriptRuntimeNodeRoot* UUAVGScript::SetupNewRuntimeScript()
{
	RootNode = NewObject<UUAVGScriptRuntimeNodeRoot>(this, UUAVGScriptRuntimeNodeRoot::StaticClass(), NAME_None, RF_Transactional);
	//AllNodes.Empty();
	AddRuntimeNode(RootNode);
	return RootNode;
}

bool UUAVGScript::AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode)
{
	//AllNodes.AddUnique(NewNode);
	return true;
}

FText UUAVGScript::HelloScript()
{
	if (RootNode)
	{
		UE_LOG(LogUAVGRuntimeScript, Warning, TEXT("Found Root Node. The Script's Name is '%s_%s' "), *GetName(), *(RootNode->ScriptName.ToString()));
	}
	else
	{
		UE_LOG(LogUAVGRuntimeScript, Error, TEXT("NO ROOT NODE FOUND ! Try To Save Script '%s' !"), *GetName());
		return FText::GetEmpty();
	}

	return FText::FromName(RootNode->ScriptName);
}
