//NTRHostage

#pragma once

#include "SGraphNode.h"
#include "SVectorInputBox.h"
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

	void CreateStandardPinWidget(UEdGraphPin* Pin) override;

	void UpdateGraphNode() override;

	void SetOwner(const TSharedRef<SGraphPanel>& OwnerPanel) override;
protected:
	void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;

	UUAVGScriptGraphNode* MyGraphNode = nullptr;

	TSharedPtr<SVerticalBox> PinBox;
};