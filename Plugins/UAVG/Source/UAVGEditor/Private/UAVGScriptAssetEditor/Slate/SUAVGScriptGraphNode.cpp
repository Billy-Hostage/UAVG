//NTRHostage

#include "SUAVGScriptGraphNode.h"
#include "UAVGScriptGraphNode.h"

void SUAVGScriptGraphNode::Construct(const FArguments& InArgs, UUAVGScriptGraphNode* InNode)
{
	GraphNode = CastChecked<UEdGraphNode>(InNode);
	MyGraphNode = InNode;
}

void SUAVGScriptGraphNode::CreatePinWidgets()
{
	
}

void SUAVGScriptGraphNode::CreateStandardPinWidget(UEdGraphPin* Pin)
{

}

void SUAVGScriptGraphNode::UpdateGraphNode()
{
	
}

void SUAVGScriptGraphNode::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{

}

void SUAVGScriptGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{

}

TSharedPtr<SGraphPin> SUAVGScriptGraphNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SGraphNode::CreatePinWidget(Pin);
}
