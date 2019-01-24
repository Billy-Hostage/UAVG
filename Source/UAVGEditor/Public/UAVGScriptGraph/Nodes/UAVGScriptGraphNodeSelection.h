//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UObject/UnrealType.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeSelection.generated.h"

//TODO Save with this node will crash
UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeSelection : public UUAVGScriptGraphNode
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
		return NSLOCTEXT("UAVGScriptGraphNode_Selection", "SelectionToolTip", "A Node to ask user for a Selection");
	}
	virtual FLinearColor GetNodeTitleColor() const override
	{
		return FLinearColor::Gray;
	}

	virtual TArray<UEdGraphPin*> GetOutputPins();

	virtual UEdGraphPin* GetInputPin() override
	{
		return Pins[0];
	}

	virtual void AllocateDefaultPins() override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
protected:
	virtual void CreateOutputPins(int32 Index);
	virtual void CreateInputPin() override;
protected:
	///Properties Here

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> Selections;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint8 DefaultSelectionIndex;
};
