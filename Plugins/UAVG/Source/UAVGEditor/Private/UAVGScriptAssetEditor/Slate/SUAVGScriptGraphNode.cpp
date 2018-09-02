//NTRHostage

#include "SUAVGScriptGraphNode.h"
#include "SUAVGScriptGraphPin.h"

#include "UAVGScriptGraphNode.h"

void SUAVGScriptGraphNode::Construct(const FArguments& InArgs, UUAVGScriptGraphNode* InNode)
{
	SetCursor(EMouseCursor::Default);
	
	GraphNode = CastChecked<UEdGraphNode>(InNode);
	MyGraphNode = InNode;

	UpdateGraphNode();
}

void SUAVGScriptGraphNode::CreatePinWidgets()
{
	UEdGraphPin* InputPin = MyGraphNode->GetInputPin();
	UEdGraphPin* OutputPin = MyGraphNode->GetOutputPin();
	if (InputPin) CreateStandardPinWidget(InputPin);
	if (OutputPin) CreateStandardPinWidget(OutputPin);
}

void SUAVGScriptGraphNode::CreateStandardPinWidget(UEdGraphPin* Pin)
{
	SGraphNode::CreateStandardPinWidget(Pin);
}

//Update The Node to match EdNode's Data
void SUAVGScriptGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();
	PinBox.Reset();
	LeftNodeBox.Reset();
	RightNodeBox.Reset();
	SAssignNew(PinBox, SVerticalBox);

	SGraphNode::UpdateGraphNode();
}

void SUAVGScriptGraphNode::SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel)
{
	SGraphNode::SetOwner(OwnerPanel);
}

void SUAVGScriptGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	PinToAdd->SetVisibility(EVisibility::Visible);

	PinBox->AddSlot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(1.0f)
		[
			PinToAdd
		];
	if (PinToAdd->GetDirection() == EGPD_Input)
	{
		InputPins.Add(PinToAdd);
	}
	else if(PinToAdd->GetDirection() == EGPD_Output)
	{
		OutputPins.Add(PinToAdd);
	}
}

TSharedPtr<SGraphPin> SUAVGScriptGraphNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SUAVGScriptGraphPin, Pin);//TODO
}
