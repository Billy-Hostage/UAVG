//NTRHostage

#include "UAVGScriptGraphNode.h"

#include "UAVGScriptRTNode.h"
#include "Framework/Commands/GenericCommands.h"

#include "EdGraph/EdGraphPin.h"
#include "EdGraph/EdGraphSchema.h"

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

void UUAVGScriptGraphNode::GetContextMenuActions(const FGraphNodeContextMenuBuilder& Context) const
{
	if (Context.Node && !IsRootNode())
	{
		Context.MenuBuilder->BeginSection("UAVGScriptGraphNode_BaseNodeEdit");

		if (CanUserDeleteNode())
			Context.MenuBuilder->AddMenuEntry(FGenericCommands::Get().Delete);
	}
}

void UUAVGScriptGraphNode::GetPinConnectedNodes(class UEdGraphPin* Pin, TArray<UUAVGScriptRuntimeNode*>& OutNodes)
{
	UUAVGScriptRuntimeNode* LinkedNode = CastChecked<UUAVGScriptRuntimeNode>
		(CastChecked<UUAVGScriptGraphNode>(Pin->GetOwningNode())->GetRTNode());
	OutNodes.Add(LinkedNode);
}
