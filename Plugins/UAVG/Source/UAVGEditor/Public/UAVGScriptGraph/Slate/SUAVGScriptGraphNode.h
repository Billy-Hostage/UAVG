//NTRHostage

#pragma once

#include "SGraphNode.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Input/DragAndDrop.h"
#include "Input/Reply.h"
#include "Editor/GraphEditor/Private/DragNode.h"

class FDragUAVGScriptGraphNode : public FDragNode
{
public:
	DRAG_DROP_OPERATOR_TYPE(FDragUAVGScriptGraphNode, FDragNode)
public:
	static TSharedRef<FDragUAVGScriptGraphNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TSharedRef<SGraphNode>& InDraggedNode);
	static TSharedRef<FDragUAVGScriptGraphNode> New(const TSharedRef<SGraphPanel>& InGraphPanel, const TArray< TSharedRef<SGraphNode> >& InDraggedNodes);

	class UUAVGScriptGraphNode* GetDropTargetNode() const;

	double StartTime;
};

class UAVGEDITOR_API SUAVGScriptGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SUAVGScriptGraphNode)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UUAVGScriptGraphNode* InNode);

	void CreatePinWidgets() override;

	void UpdateGraphNode() override;

	void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);
	FReply OnMouseDown(const FGeometry& SenderGeometry, const FPointerEvent& MouseEvent);
protected:
	TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;

	UUAVGScriptGraphNode* MyGraphNode = nullptr;

	TSharedPtr<class SHorizontalBox> OutputPinBox;

	TSharedPtr<class SBorder> NodeBody;

	TSharedPtr<SInlineEditableTextBlock> NodeTextBlock;

	FSlateColor GetNodeTitleColor() const;

	FSlateColor GetNodeBackgroundColor() const;
};