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

bool UUAVGScriptGraphNode::IsInputPin(UEdGraphPin* PinToCheck)
{
	return PinToCheck == GetInputPin();
}
bool UUAVGScriptGraphNode::IsOutputPin(UEdGraphPin* PinToCheck)
{
	return PinToCheck == GetOutputPin();
}

void UUAVGScriptGraphNode::PostPasteNode()
{
	Super::PostPasteNode();
	MyRTNode = nullptr;
}

void UUAVGScriptGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node && !IsRootNode())
	{
		//Context.MenuBuilder->BeginSection("UAVGScriptGraphNode_BaseNodeEdit");
		auto& section = Menu->AddSection("UAVGScriptGraphNode_BaseNodeEdit", FText::FromString("Edit"));

		if (CanUserDeleteNode())
			section.AddMenuEntry(FGenericCommands::Get().Delete);
		if (CanDuplicateNode())
		{
			section.AddMenuEntry(FGenericCommands::Get().Duplicate);
			section.AddMenuEntry(FGenericCommands::Get().Copy);
		}
	}
}

void UUAVGScriptGraphNode::GetAllConnectedScriptNodes(TArray<UUAVGScriptGraphNode*>& OutNodes)
{
	if (GetInputPin())
	{
		GetPinConnectedScriptNodes(GetInputPin(), OutNodes);
	}
	if (GetOutputPin())
	{
		GetPinConnectedScriptNodes(GetOutputPin(), OutNodes);
	}
}

void UUAVGScriptGraphNode::GetPinConnectedNodes(class UEdGraphPin* Pin, TArray<UUAVGScriptRuntimeNode*>& OutNodes)
{
	UUAVGScriptRuntimeNode* LinkedNode = CastChecked<UUAVGScriptRuntimeNode>
		(CastChecked<UUAVGScriptGraphNode>(Pin->GetOwningNode())->GetRTNode());
	OutNodes.Add(LinkedNode);
}

void UUAVGScriptGraphNode::GetPinConnectedScriptNodes(UEdGraphPin* Pin, TArray<UUAVGScriptGraphNode*>& OutNodes)
{
	auto LinkedTo = Pin->LinkedTo;
	for (auto P : LinkedTo)
	{
		OutNodes.Add(CastChecked<UUAVGScriptGraphNode>(P->GetOwningNode()));
	}
}
