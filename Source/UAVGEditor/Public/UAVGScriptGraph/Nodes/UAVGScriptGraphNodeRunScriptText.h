//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeRunScriptText.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeRunScriptText : public UUAVGScriptGraphNode
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
		return NSLOCTEXT("UAVGScriptGraphNode_RunScriptText", "RunScriptTextToolTip", "A Node to Run(Interpret) UAVG Script Text.");
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Yellow;
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
	///Prperties Here

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Script Text", ToolTip = "The ScriptText to Run"))
	class UUAVGScriptText* ScriptText;
};
