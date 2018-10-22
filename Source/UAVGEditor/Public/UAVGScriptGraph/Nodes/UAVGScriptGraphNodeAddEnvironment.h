//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeAddEnvironment.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeAddEnvironment : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	virtual bool IsUserCreatableNode()const override
	{
		return true;
	}
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
	virtual bool IsRootNode() const override
	{
		return false;
	}

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override
	{
		return NSLOCTEXT("UAVGScriptGraphNode_AddEnvironment", "AddEnvironmentToolTip", "A Node to Add a Environment descriptor");
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Green;
	}

	virtual UEdGraphPin* GetOutputPin() override
	{
		return Pins[1];
	}
	virtual UEdGraphPin* GetInputPin() override
	{
		return Pins[0];
	}


protected:

protected:
	///Properties Here

};