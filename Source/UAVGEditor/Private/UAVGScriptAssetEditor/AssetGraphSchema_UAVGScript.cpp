//NTRHostage

#include "UAVGScriptGraph/AssetGraphSchema_UAVGScript.h"
#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNodeRoot.h"
#include "UAVGScriptGraph/EdGraph_UAVGScript.h"
#include "UAVGScript.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "NewNode_UAVGScriptGraphSchemaAction"

TArray<TSubclassOf<UUAVGScriptGraphNode>> UAssetGraphSchema_UAVGScript::ScriptGraphNodeClasses;
const FText UAssetGraphSchema_UAVGScript::NODE_CATEGORY_NormalNode(LOCTEXT("UAVGScriptNormalNodeAction", "Normal Nodes"));
bool UAssetGraphSchema_UAVGScript::bIsNodeClassesInitialized = false;

namespace
{
	// Maximum distance a drag can be off a node edge to require 'push off' from node
	const int32 NodeDistance = 60;
}

UAssetGraphSchema_UAVGScript::UAssetGraphSchema_UAVGScript(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UAssetGraphSchema_UAVGScript::GetPaletteActions(FGraphActionMenuBuilder& OutActions) const
{
	GetAllUAVGScriptGraphNodeActions(OutActions);
}

void UAssetGraphSchema_UAVGScript::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	GetAllUAVGScriptGraphNodeActions(ContextMenuBuilder);
}

void UAssetGraphSchema_UAVGScript::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	check(Graph.IsA(UEdGraph_UAVGScript::StaticClass()));
	UEdGraph_UAVGScript* ScriptGraph = CastChecked<UEdGraph_UAVGScript>(&Graph);
	
	ScriptGraph->CreateNode(TSubclassOf<UUAVGScriptGraphNodeRoot>(UUAVGScriptGraphNodeRoot::StaticClass()), 0, 0, true, false);

	Super::CreateDefaultNodesForGraph(Graph);
}

const FPinConnectionResponse UAssetGraphSchema_UAVGScript::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	UUAVGScriptGraphNode* ANode = CastChecked<UUAVGScriptGraphNode>(A->GetOwningNode());
	UUAVGScriptGraphNode* BNode = CastChecked<UUAVGScriptGraphNode>(B->GetOwningNode());
	if (ANode == BNode)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("CanCreateConnectionMessage_SameNode", "Can't connect to self!"));
	}
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, LOCTEXT("CanCreateConnectionMessage_WrongDirection", "Output Pin can only connects with Input Pin"));
	}
	// find out which pin is the output one, we want output pins having only one node connected to
	if (A->Direction == EGPD_Output)
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_A, LOCTEXT("CanCreateConnectionMessage_OK", "Created Link"));
	else
		return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_B, LOCTEXT("CanCreateConnectionMessage_OK", "Created Link"));
}

bool UAssetGraphSchema_UAVGScript::SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const
{
	UUAVGScriptGraphNode* UNode = CastChecked<UUAVGScriptGraphNode>(Node);
	if (UNode->CanUserDeleteNode())
	{
		//TODO
		//return true;
	}
	return false;
}

void UAssetGraphSchema_UAVGScript::InitializeAllNodeClass()
{
	if (bIsNodeClassesInitialized)
	{
		return;
	}

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UUAVGScriptGraphNode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			ScriptGraphNodeClasses.Add(*It);
		}
	}
	
	bIsNodeClassesInitialized = true;
}

void UAssetGraphSchema_UAVGScript::GetAllUAVGScriptGraphNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder) const
{
	InitializeAllNodeClass();

	FText ToolTip, MenuDesc;
	// when dragging from an input pin
	if (ActionMenuBuilder.FromPin == nullptr)
	{
		// Just right clicked on the empty graph
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip", "Adds {Name} to graph");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription", "{Name}");
	}
	else if (ActionMenuBuilder.FromPin->Direction == EGPD_Input)
	{
		// From an input pin
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip_FromInputPin", "Adds {Name} as parent");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription_FromInputPin", "{Name}");
	}
	else
	{
		// From an output pin
		check(ActionMenuBuilder.FromPin->Direction == EGPD_Output);
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip_FromOutputPin", "Adds {Name} as child");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription_FromOutputPin", "{Name}");
	}


	int32 Grouping = 0;
	FFormatNamedArguments Args;
	for (auto NodeClass : ScriptGraphNodeClasses)
	{
		const UUAVGScriptGraphNode* NodePtr = NodeClass->GetDefaultObject<UUAVGScriptGraphNode>();
		if (!NodePtr->IsUserCreatableNode()) continue;//Sikp some node
		Args.Add(TEXT("Name"), NodePtr->GetNodeTitle(ENodeTitleType::ListView));
		TSharedPtr<FNewNode_UAVGScriptGraphSchemaAction> Action(new FNewNode_UAVGScriptGraphSchemaAction(NODE_CATEGORY_NormalNode, FText::Format(MenuDesc, Args), FText::Format(ToolTip, Args), Grouping, NodeClass));
		ActionMenuBuilder.AddAction(Action);
	}
}

FNewNode_UAVGScriptGraphSchemaAction::FNewNode_UAVGScriptGraphSchemaAction()
	:Super()
{
}

FNewNode_UAVGScriptGraphSchemaAction::FNewNode_UAVGScriptGraphSchemaAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, int32 InGrouping, TSubclassOf<class UUAVGScriptGraphNode> InCreateNodeType)
	:Super(InNodeCategory, InMenuDesc, InToolTip, InGrouping), CreateNodeType(InCreateNodeType)
{
	
}

UEdGraphNode* FNewNode_UAVGScriptGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /*= true*/)
{
	const FScopedTransaction Transaction(LOCTEXT("UAVGScriptEditorNewNode", "UAVGScript Editor: New Node"));
	//TODO Undo will crash editor cus Node in editor is not "Removed"
	UUAVGScript* Script = CastChecked<UEdGraph_UAVGScript>(ParentGraph)->GetUAVGScript();

	verify(ParentGraph->Modify());
	if (FromPin)
	{
		verify(FromPin->Modify());
	}
	verify(Script->Modify());

	UEdGraphNode* NewNode = CastChecked<UEdGraph_UAVGScript>(ParentGraph)->CreateNode(CreateNodeType, Location.X, Location.Y, bSelectNewNode);

	int32 XLocation = Location.X;
	if (FromPin && FromPin->Direction == EGPD_Input)
	{
		UEdGraphNode* PinNode = FromPin->GetOwningNode();
		const float XDelta = FMath::Abs(PinNode->NodePosX - Location.X);

		if (XDelta < NodeDistance)
		{
			XLocation = PinNode->NodePosX - NodeDistance;
		}
	}
	NewNode->NodePosX = XLocation;
	NewNode->NodePosY = Location.Y;
	NewNode->SnapToGrid(16);
	NewNode->AutowireNewNode(FromPin);
	return NewNode;
}

#undef LOCTEXT_NAMESPACE