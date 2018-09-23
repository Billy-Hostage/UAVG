//NTRHostage

#include "EdGraph_UAVGScript.h"
#include "UAVGScriptGraphNodeRoot.h"

#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"

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
	//TODO Undo Buffer
	return Super::Modify(bAlwaysMarkDirty);
}

UUAVGScriptGraphNode* UEdGraph_UAVGScript::CreateNode(TSubclassOf<UUAVGScriptGraphNode> NodeClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode /*= true*/, bool bIsUserAction /*= true*/)
{
	UUAVGScriptGraphNode* ResultNode = nullptr;

	ResultNode = NewObject<UUAVGScriptGraphNode>(this, NodeClass.Get(), NAME_None, RF_Transactional);

	ResultNode->CreateNewGuid();
	ResultNode->PostPlacedNewNode();
	ResultNode->AllocateDefaultPins();
	ResultNode->SetupRTNode(GetUAVGScript());

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

UUAVGScriptGraphNodeRoot* UEdGraph_UAVGScript::GetRootNode()
{
	TArray<UUAVGScriptGraphNodeRoot*> RootNodeList;
	GetNodesOfClass<UUAVGScriptGraphNodeRoot>(RootNodeList);
	check(RootNodeList.Num() == 1 && RootNodeList[0]);
	return RootNodeList[0];
}

void UEdGraph_UAVGScript::RebulidRuntimeScript()
{
	UUAVGScript* EditingScript = GetUAVGScript();

	UUAVGScriptGraphNode* GraphNode = nullptr;
	for (int32 index = 0; index < Nodes.Num(); ++index)
	{
		GraphNode = CastChecked<UUAVGScriptGraphNode>(Nodes[index]);
		GraphNode->SaveToRTNode(EditingScript);
	}
}
