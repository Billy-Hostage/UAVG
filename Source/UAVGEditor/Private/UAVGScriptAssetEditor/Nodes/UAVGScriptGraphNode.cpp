//NTRHostage

#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNode.h"

#include "Nodes/UAVGScriptRTNode.h"
#include "Framework/Commands/GenericCommands.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"

#include "ToolMenus/Public/ToolMenu.h"

DEFINE_LOG_CATEGORY(LogUAVGScriptGraphNode);

UUAVGScriptGraphNode::UUAVGScriptGraphNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNode::SaveToRTNode(class UUAVGScript* RTScript)
{
	check(RTScript);

	TArray<UUAVGScriptRuntimeNode*> ParentRTNodes;
	TArray<UUAVGScriptRuntimeNode*> ChildRTNodes;

	if (GetInputPin() != nullptr)//Get Parent Nodes
	{
		UUAVGScriptRuntimeNode* LinkedNode = nullptr;
		TArray<UEdGraphPin*> LinkedPins = GetInputPin()->LinkedTo;
		for (UEdGraphPin* Pin : LinkedPins)
		{
			if (!Pin) continue;
			
			GetPinConnectedNodes(Pin, ParentRTNodes);
		}
	}
	if (GetOutputPin() != nullptr)//Get Child Nodes
	{
		UUAVGScriptRuntimeNode* LinkedNode = nullptr;
		TArray<UEdGraphPin*> LinkedPins = GetOutputPin()->LinkedTo;
		for (UEdGraphPin* Pin : LinkedPins)
		{
			if (!Pin) continue;

			GetPinConnectedNodes(Pin, ChildRTNodes);
		}
	}

	if (!(MyRTNode->SetParent(ParentRTNodes) && MyRTNode->SetChild(ChildRTNodes)))
	{
		UE_LOG(LogUAVGScriptGraphNode, Error, TEXT("Parent || Child Binding Failed at Node %s"), *GetName());
	}
}

void UUAVGScriptGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);
	if (FromPin != nullptr)
	{
		UEdGraphPin* OutputPin = GetOutputPin();

		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
		else if (OutputPin != nullptr && GetSchema()->TryCreateConnection(OutputPin, FromPin))
		{
			NodeConnectionListChanged();
		}
	}
}

void UUAVGScriptGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node && !IsRootNode())
	{
		//Context.MenuBuilder->BeginSection("UAVGScriptGraphNode_BaseNodeEdit");
		auto& section = Menu->AddSection("UAVGScriptGraphNode_BaseNodeEdit", FText::FromString("Edit"));

		if (CanUserDeleteNode())
			section.AddMenuEntry(FGenericCommands::Get().Delete);
	}
}

void UUAVGScriptGraphNode::GetPinConnectedNodes(class UEdGraphPin* Pin, TArray<UUAVGScriptRuntimeNode*>& OutNodes)
{
	UUAVGScriptRuntimeNode* LinkedNode = CastChecked<UUAVGScriptRuntimeNode>
		(CastChecked<UUAVGScriptGraphNode>(Pin->GetOwningNode())->GetRTNode());
	OutNodes.Add(LinkedNode);
}
