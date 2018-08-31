//NTRHostage

#include "AssetGraphSchema_UAVGScript.h"
#include "UAVGScriptGraphNodeRoot.h"
#include "EdGraph_UAVGScript.h"
#include "UAVGScript.h"

#define LOCTEXT_NAMESPACE "NewNode_UAVGScriptGraphSchemaAction"

TArray<TSubclassOf<UUAVGScriptGraphNode>> UAssetGraphSchema_UAVGScript::ScriptGraphNodeClasses;
const FText UAssetGraphSchema_UAVGScript::NODE_CATEGORY_NormalNode(LOCTEXT("UAVGScriptNormalNodeAction", "Normal Nodes"));
bool UAssetGraphSchema_UAVGScript::bIsNodeClassesInitialized = false;

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
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip", "Adds {Name} to the graph");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription", "{Name}");
	}
	else if (ActionMenuBuilder.FromPin->Direction == EGPD_Input)
	{
		// From an input pin
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip_FromInputPin", "Adds {Name} to the graph as a parent to the current node");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription_FromInputPin", "Add {Name} parent");
	}
	else
	{
		// From an output pin
		check(ActionMenuBuilder.FromPin->Direction == EGPD_Output);
		ToolTip = LOCTEXT("NewUAVGScriptNodeTooltip_FromOutputPin", "Adds {Name} to the graph as a child to the current node");
		MenuDesc = LOCTEXT("NewUAVGScriptNodeMenuDescription_FromOutputPin", "Add {Name} child");
	}


	int32 Grouping = 0;
	FFormatNamedArguments Args;
	for (auto NodeClass : ScriptGraphNodeClasses)
	{
		const UUAVGScriptGraphNode* NodePtr = NodeClass->GetDefaultObject<UUAVGScriptGraphNode>();
		if (!NodePtr->IsUserCreatable()) continue;
		Args.Add(TEXT("Name"), NodePtr->GetNodeTitle(ENodeTitleType::MenuTitle));
		TSharedPtr<FNewNode_UAVGScriptGraphSchemaAction> Action(new FNewNode_UAVGScriptGraphSchemaAction(NODE_CATEGORY_NormalNode, FText::Format(MenuDesc, Args), FText::Format(ToolTip, Args), Grouping++, NodeClass));
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
	UUAVGScript* Script = CastChecked<UEdGraph_UAVGScript>(ParentGraph)->GetUAVGScript();

	verify(ParentGraph->Modify());
	if (FromPin)
	{
		verify(FromPin->Modify());
	}
	verify(Script->Modify());

	return CastChecked<UEdGraph_UAVGScript>(ParentGraph)->CreateNode(CreateNodeType, Location.X, Location.Y, bSelectNewNode);
}

#undef LOCTEXT_NAMESPACE