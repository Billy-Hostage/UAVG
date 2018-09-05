//NTRHostage

#pragma once

#include "SGraphNode.h"
#include "Widgets/DeclarativeSyntaxSupport.h"

class SUAVGScriptGraphNode : public SGraphNode
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
protected:
	TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;

	UUAVGScriptGraphNode* MyGraphNode = nullptr;

	TSharedPtr<class SHorizontalBox> OutputPinBox;

	TSharedPtr<class SBorder> NodeBody;

	TSharedPtr<SInlineEditableTextBlock> NodeTextBlock;
};