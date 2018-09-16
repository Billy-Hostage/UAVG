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
	UUAVGScriptGraphNodeRoot* RootNode = GetRootNode();
	UUAVGScript* EditingScript = GetUAVGScript();

	//Save Root Node first
	EditingScript->ClearNode();
	RootNode->MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(EditingScript->SetupNewRuntimeRootNode());

	for (UEdGraphNode* Node : Nodes)
	{
		if(Node == RootNode) continue;//Skip Root Node
		//TODO
	}
}
