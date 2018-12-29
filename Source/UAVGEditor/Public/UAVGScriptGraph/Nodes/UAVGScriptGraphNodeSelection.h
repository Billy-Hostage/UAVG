//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeSelection.generated.h"

//TODO
UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeSelection : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	//virtual void SetupRTNode(class UUAVGScript* RTScript) override;
	//virtual void SaveToRTNode(class UUAVGScript* RTScript) override;

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
		return NSLOCTEXT("UAVGScriptGraphNode_Selection", "SelectionToolTip", "A Node to ask user for a Selection");
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Gray;
	}

	virtual UEdGraphPin* GetInputPin() override
	{
		return Pins[0];
	}

	virtual void AllocateDefaultPins() override;
protected:
	void CreateOutputPin(int32 Index);
	virtual void CreateInputPin() override;
protected:
	///Properties Here
};
