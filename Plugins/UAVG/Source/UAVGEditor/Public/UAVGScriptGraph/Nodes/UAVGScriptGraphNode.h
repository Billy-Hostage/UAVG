//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "EditorStyle.h"
#include "UAVGScriptGraphNode.generated.h"

class UEdGraphPin;
class UUAVGScriptRuntimeNode;

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGScriptGraphNode, Log, All);

//Abstract Base Node Class
UCLASS(Abstract, MinimalAPI)
class UUAVGScriptGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

public:
	virtual void SaveToRTNode(class UUAVGScript* RTScript);

	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;

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
		return FLinearColor::Black;
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

	virtual bool IsUserCreatableNode() const
	{
		return true;
	}
	virtual bool IsRootNode() const
	{
		return false;
	}

	virtual UEdGraphPin* GetInputPin()
	{
		return nullptr;
	}
	virtual UEdGraphPin* GetOutputPin()
	{
		return nullptr;
	}

	virtual void SetupRTNode(class UUAVGScript* RTScript)
	{
		unimplemented();
	}
	UUAVGScriptRuntimeNode* GetRTNode()
	{
		return MyRTNode;
	}

	virtual void GetContextMenuActions(const FGraphNodeContextMenuBuilder& Context) const override;
protected:
	virtual void CreateInputPin()
	{
		unimplemented();
	}
	virtual void CreateOutputPin()
	{
		unimplemented();
	}

	UPROPERTY()
	UUAVGScriptRuntimeNode* MyRTNode = nullptr;
private:
	static void GetPinConnectedNodes(class UEdGraphPin* Pin, TArray<UUAVGScriptRuntimeNode*>& OutNodes);
};
