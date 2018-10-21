//NTRHostage

#pragma once

#include "SGraphPin.h"

class UAVGEDITOR_API SUAVGScriptGraphPin : public SGraphPin
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
		return FSlateColor(IsHovered() ? FLinearColor::Yellow : FLinearColor::Gray);
	}

	virtual const FSlateBrush* GetPinBorder() const
	{
		return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
	}
};
