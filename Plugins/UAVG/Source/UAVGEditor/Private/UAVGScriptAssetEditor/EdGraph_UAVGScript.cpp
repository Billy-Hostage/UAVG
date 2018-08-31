//NTRHostage

#include "EdGraph_UAVGScript.h"
#include "UAVGScript.h"
#include "UAVGScriptGraphNode.h"

UEdGraph_UAVGScript::UEdGraph_UAVGScript()
{

}

UEdGraph_UAVGScript::~UEdGraph_UAVGScript()
{

}

bool UEdGraph_UAVGScript::Modify(bool bAlwaysMarkDirty /*= true*/)
{
	if (!CanModify())
	{
		return false;
	}

	bool bWasSaved = Super::Modify(bAlwaysMarkDirty);
	//TODO Here
	return bWasSaved;
}

UUAVGScriptGraphNode* UEdGraph_UAVGScript::CreateNode(TSubclassOf<UUAVGScriptGraphNode> NodeClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode /*= true*/)
{
	return nullptr;
}

UUAVGScript* UEdGraph_UAVGScript::GetUAVGScript() const
{
	return CastChecked<UUAVGScript>(GetOuter());
}
