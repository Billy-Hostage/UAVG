//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "UAVGScriptGraphConnectionDrawingPolicy.h"
#include "AssetGraphSchema_UAVGScript.generated.h"

USTRUCT()
struct UAVGEDITOR_API FNewNode_UAVGScriptGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY()
public:
	FNewNode_UAVGScriptGraphSchemaAction();
	FNewNode_UAVGScriptGraphSchemaAction(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip,
		int32 InGrouping, TSubclassOf<class UUAVGScriptGraphNode> InCreateNodeType);

	UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
private:
	TSubclassOf<class UUAVGScriptGraphNode> CreateNodeType;
};

UCLASS(MinimalAPI)
class UAssetGraphSchema_UAVGScript : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()
public:
	virtual void GetPaletteActions(FGraphActionMenuBuilder& OutActions) const;

	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	virtual void CreateDefaultNodesForGraph(class UEdGraph& Graph) const override;

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override
	{
		return new FUAVGScriptGraphConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	}

	virtual bool SafeDeleteNodeFromGraph(UEdGraph* Graph, UEdGraphNode* Node) const override;
private:
	/** Adds actions for creating every type of DialogueNode */
	void GetAllUAVGScriptGraphNodeActions(FGraphActionMenuBuilder& ActionMenuBuilder) const;

	static void InitializeAllNodeClass();

	/** A list of all available UDlgNode classes */
	static TArray<TSubclassOf<class UUAVGScriptGraphNode>> ScriptGraphNodeClasses;

	static bool bIsNodeClassesInitialized;

	static const FText NODE_CATEGORY_NormalNode;
	static const FText NODE_CATEGORY_Graph;
};