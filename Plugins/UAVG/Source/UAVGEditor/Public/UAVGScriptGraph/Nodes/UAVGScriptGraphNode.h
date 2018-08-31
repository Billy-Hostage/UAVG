//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "UAVGScriptGraphNode.generated.h"

class UEdGraphPin;

//Abstract Base Node Class
UCLASS(Abstract, MinimalAPI)
class UUAVGScriptGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:
	virtual bool CanDuplicateNode() const override
	{
		return true;
	}
	virtual bool CanUserDeleteNode() const override
	{
		return true;
	}
	virtual bool CanSplitPin(const UEdGraphPin* Pin) const override
	{
		return false;
	}
	virtual bool ShowPaletteIconOnNode() const override
	{
		return true;
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return GetNodeBackgroundColor();
	}
	virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override
	{
		static const FSlateIcon Icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Graph.StateNode.Icon");
		OutColor = GetNodeBackgroundColor();
		return Icon;
	}

	virtual FLinearColor GetNodeBackgroundColor() const
	{
		return FLinearColor::Black;
	}
	
	FVector2D GetPosition() const
	{
		return FVector2D(NodePosX, NodePosY);
	}

	void SetPosition(const FVector2D& NewPosition)
	{
		NodePosX = NewPosition.X;
		NodePosY = NewPosition.Y;
	}

	virtual bool IsUserCreatable() const
	{
		return false;
	}
	virtual bool IsRootNode() const
	{
		return false;
	}
protected:
	virtual void CreateInputPin()
	{
	};
	virtual void CreateOutputPin()
	{
	};
};
