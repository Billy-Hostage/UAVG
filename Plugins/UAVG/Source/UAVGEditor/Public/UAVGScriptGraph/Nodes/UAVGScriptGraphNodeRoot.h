//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeRoot.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeRoot : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	virtual bool CanDuplicateNode() const override
	{
		return false;
	}
	virtual bool CanUserDeleteNode() const override
	{
		return false;
	}
	virtual bool CanSplitPin(const UEdGraphPin* Pin) const override
	{
		return false;
	}
	virtual bool ShowPaletteIconOnNode() const override
	{
		return false;
	}

	virtual bool IsUserCreatableNode() const override
	{
		return false;
	}

	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return NSLOCTEXT("UAVGScriptGraphNode_Root", "RootTitle", "Root");
	}

	FText GetTooltipText() const override
	{
		return NSLOCTEXT("UAVGScriptGraphNode_Root", "RootToolTip", "The root start node of this graph");
	}
	FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Green;
	}

	virtual bool IsRootNode() const override
	{
		//This is a root node.
		return true;
	}

	UEdGraphPin* GetOutputPin() override
	{
		return Pins[0];
	}

	void AllocateDefaultPins() override;
private:
protected:
	void CreateOutputPin() override;
};