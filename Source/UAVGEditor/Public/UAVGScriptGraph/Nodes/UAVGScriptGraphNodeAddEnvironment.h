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
		return NSLOCTEXT("UAVGScriptGraphNode_AddEnvironment", "AddEnvironmentToolTip", "A Node to Add a Environment Descriptor");
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

	virtual void AllocateDefaultPins() override;
protected:
	virtual void CreateOutputPin() override;
	virtual void CreateInputPin() override;
protected:
	///Properties Here

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Environment Descriptor", ToolTip = "The Environment String Descriptor to Add"))
	FString EnvironmentToAdd;

	UPROPERTY(EditAnywhere, meta = (ToolTip = "Additional Arguments Being Passed When Calling Events in Interfaces"))
	TArray<FString> AdditonalArguments;
};
