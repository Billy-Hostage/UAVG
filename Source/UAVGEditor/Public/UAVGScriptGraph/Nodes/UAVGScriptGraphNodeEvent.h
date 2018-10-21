//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeEvent.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeEvent : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	virtual void SetupRTNode(class UUAVGScript* RTScript) override;
	virtual void SaveToRTNode(class UUAVGScript* RTScript) override;

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
		return NSLOCTEXT("UAVGScriptGraphNode_Event", "EventToolTip", "A Node to Trigger Custom Event");
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Red;
	}

	virtual UEdGraphPin* GetOutputPin() override
	{
		return Pins[1];
	}
	virtual UEdGraphPin* GetInputPin() override
	{
		return Pins[0];
	}

	virtual void AllocateDefaultPins() override;
protected:
	virtual void CreateOutputPin() override;
	virtual void CreateInputPin() override;
protected:
	///Properties Here

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Event Name", ToolTip = "The Name of Custom Event"))
	FString EventName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Event Arguments", ToolTip = "The Arguments passed to the Event"))
	TArray<FString> Arguments;
};
