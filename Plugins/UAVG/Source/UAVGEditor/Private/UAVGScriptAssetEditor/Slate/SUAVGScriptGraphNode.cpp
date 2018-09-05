//NTRHostage

#include "SUAVGScriptGraphNode.h"
#include "SUAVGScriptGraphPin.h"

#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "Widgets/SBoxPanel.h"

#include "UAVGScriptGraphNode.h"

void SUAVGScriptGraphNode::Construct(const FArguments& InArgs, UUAVGScriptGraphNode* InNode)
{
	check(InNode);

	SetCursor(EMouseCursor::CardinalCross);
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

//Update The Node to match EdNode's Data
void SUAVGScriptGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();
	OutputPinBox.Reset();

	//TODO initialize Decorators and Services

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);
	TWeakPtr<SNodeTitle> WeakNodeTitle = NodeTitle;

	const FMargin NodePadding(8.f);
	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(0.0f)
			.BorderBackgroundColor(FSlateColor(FLinearColor::Black))
			//.OnMouseButtonDown(TODO)
			[
				SNew(SOverlay)

				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)

					//Input Pin Goes Here
					+SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SBox)
						.MinDesiredHeight(NodePadding.Top)
						[
							SAssignNew(LeftNodeBox, SVerticalBox)
						]
					]

					//Description Aera
					+SVerticalBox::Slot()
					.Padding(FMargin(NodePadding.Left, 0.f, NodePadding.Right, 0.f))
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						//[
							//TODO Decorators
						//]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(NodeBody, SBorder)
							.BorderImage(FEditorStyle::GetBrush("BTEditor.Graph.BTNode.Body"))
							.BorderBackgroundColor(FSlateColor(FLinearColor::Black))
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Visibility(EVisibility::SelfHitTestInvisible)
							[
								SNew(SOverlay)
								+ SOverlay::Slot()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								[
									SNew(SVerticalBox)//TODO LOD Support
									+SVerticalBox::Slot()
									.AutoHeight()
									[
										SNew(SHorizontalBox)
										+SHorizontalBox::Slot()
										.AutoWidth()
										[
											SNew(SHorizontalBox)
											+SHorizontalBox::Slot()
											.AutoWidth()
											.VAlign(VAlign_Center)
											//[
												//TODO Node Icon
											//]
											+SHorizontalBox::Slot()
											.Padding(FMargin(4.f, 0.f, 4.f, 0.f))
											[
												SNew(SVerticalBox)
												+SVerticalBox::Slot()
												.AutoHeight()
												[
													SAssignNew(NodeTextBlock, SInlineEditableTextBlock)
													.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
													.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
												]
												+SVerticalBox::Slot()
												.AutoHeight()
												[
													NodeTitle.ToSharedRef()
												]
											]
										]
									]
									+SVerticalBox::Slot()
									.AutoHeight()
									//[
										//TODO Description Message
									//]
								]
							]
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						.Padding(FMargin(10.f, 0.f, 0.f, 0.f))
						//[
							//TODO Services
						//]
					]
					//OUTPUT PIN
					+SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SBox)
						.MinDesiredHeight(NodePadding.Bottom)
						[
							SAssignNew(RightNodeBox, SVerticalBox)
							+ SVerticalBox::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Fill)
							.Padding(20.0f, 0.0f)
							.FillHeight(1.0f)
							[
								SAssignNew(OutputPinBox, SHorizontalBox)
							]
						]
					]
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SNew(SBorder)
					.BorderBackgroundColor(FLinearColor::Black)
					.BorderImage(FEditorStyle::GetBrush("BTEditor.Graph.BTNode.Body"))
					.Visibility(EVisibility::Visible)
					[
						SNew(SBox)
						.HeightOverride(4)
					]
				]
			]
		];

	CreatePinWidgets();
}

void SUAVGScriptGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	PinToAdd->SetVisibility(EVisibility::Visible);

	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		const bool bIsSingleTaskPin = false;//TODO
		if (bIsSingleTaskPin)
		{
			OutputPinBox->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(0.4f)
				.Padding(0, 0, 20.0f, 0)
				[
					PinToAdd
				];
		}
		else
		{
			OutputPinBox->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(1.0f)
				[
					PinToAdd
				];
		}
		OutputPins.Add(PinToAdd);
	}
}

TSharedPtr<SGraphPin> SUAVGScriptGraphNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SUAVGScriptGraphPin, Pin);
}
