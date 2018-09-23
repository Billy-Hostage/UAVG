//NTRHostage

#include "UAVGScriptGraphNode.h"

#include "UAVGScriptRTNode.h"

UUAVGScriptGraphNode::UUAVGScriptGraphNode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNode::SaveToRTNode(class UUAVGScript* RTScript)
{
	check(RTScript);

	TArray<UUAVGScriptRuntimeNode*> ParentRTNodes;
	TArray<UUAVGScriptRuntimeNode*> ChildRTNodes;

	if (GetInputPin() != nullptr)
	{
		UUAVGScriptRuntimeNode* LinkedNode = nullptr;
		TArray<UEdGraphPin*> LinkedPins = GetInputPin()->LinkedTo;
		for (UEdGraphPin* Pin : LinkedPins)
		{
			if (!Pin) continue;
			LinkedNode = CastChecked<UUAVGScriptRuntimeNode>
				(CastChecked<UUAVGScriptGraphNode>(Pin->GetOwningNode())->GetRTNode());
			if (LinkedNode)
				ParentRTNodes.Add(LinkedNode);
		}
	}
	if (GetOutputPin() != nullptr)
	{
		UUAVGScriptRuntimeNode* LinkedNode = nullptr;
		TArray<UEdGraphPin*> LinkedPins = GetOutputPin()->LinkedTo;
		for (UEdGraphPin* Pin : LinkedPins)
		{
			if (!Pin) continue;
			LinkedNode = CastChecked<UUAVGScriptRuntimeNode>
				(CastChecked<UUAVGScriptGraphNode>(Pin->GetOwningNode())->GetRTNode());
			if (LinkedNode)
				ChildRTNodes.Add(LinkedNode);
		}
	}

	MyRTNode->SetParent(ParentRTNodes);
	MyRTNode->SetChild(ChildRTNodes);
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
