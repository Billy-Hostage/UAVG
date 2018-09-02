//NTRHostage

#pragma once

#include "SGraphPin.h"

class SUAVGScriptGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SUAVGScriptGraphPin)
	{
	}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, class UEdGraphPin* InPin);
private:
	virtual FSlateColor GetPinColour() const
	{
		return FSlateColor(FLinearColor::White);
	}

	virtual const FSlateBrush* GetPinBorder() const
	{
		return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}
};
