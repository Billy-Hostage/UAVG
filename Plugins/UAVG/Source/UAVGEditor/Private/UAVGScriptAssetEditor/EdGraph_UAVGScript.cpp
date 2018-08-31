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
	//TODO Save data to UAVGScript Here
	return bWasSaved;
}

UUAVGScriptGraphNode* UEdGraph_UAVGScript::CreateNode(TSubclassOf<UUAVGScriptGraphNode> NodeClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode /*= true*/, bool bIsUserAction /*= true*/)
{
	UUAVGScriptGraphNode* ResultNode = nullptr;

	ResultNode = NewObject<UUAVGScriptGraphNode>(this, NodeClass.Get(), NAME_None, RF_Transactional);
	
	ResultNode->PostPlacedNewNode();
	ResultNode->AllocateDefaultPins();
	
	this->AddNode(ResultNode, bIsUserAction, bSelectNewNode);
	GetUAVGScript()->PostEditChange();
	GetUAVGScript()->MarkPackageDirty();
	NotifyGraphChanged();

	return ResultNode;
}

UUAVGScript* UEdGraph_UAVGScript::GetUAVGScript() const
{
	return CastChecked<UUAVGScript>(GetOuter());
}
