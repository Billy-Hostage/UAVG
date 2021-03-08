//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "Nodes/UAVGScriptRTNodeRoot.h"
#include "UAVGScriptGraphNodeRoot.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeRoot : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	void SaveToRTNode(class UUAVGScript* RTScript) override;

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
		return FLinearColor::Gray;
	}

	bool IsRootNode() const override
	{
		//This is a root node.
		return true;
	}

	UEdGraphPin* GetOutputPin() override
	{
		return Pins[0];
	}

	void AllocateDefaultPins() override;

	void SetupRTNode(class UUAVGScript* RTScript) override;
protected:
	void CreateOutputPin() override;
protected:
	///Properties Here

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General", meta = (DisplayName = "Script Name", ToolTip = "This might not be unique"))
	FName ScriptName = "UAVGScirpt";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (DisplayName = "Fallback Character Display Delay (ms)"))
	uint8 CharacterDisplayDelayInMs = 50;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (DisplayName = "Script Completed Behaviour", ToolTip = "What to do when this script has completed"))
	EUAVGScriptCompleteBehaviour OnScriptCompleted = EUAVGScriptCompleteBehaviour::USCB_Nothing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (DisplayName = "Script To Jump",  ToolTip = "The script to jump to if you set OnScriptCompleted to Jump to Another Script"))
	class UUAVGScript* ScriptToJump = nullptr;
};
