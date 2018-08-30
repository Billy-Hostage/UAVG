//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
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
	UEdGraphNode* CreateNode(class UUAVGScript* Script, UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode);

	TSubclassOf<class UUAVGScriptGraphNode> CreateNodeType;
};

UCLASS(MinimalAPI)
class UAssetGraphSchema_UAVGScript : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()
public:
	/**
	* Get all actions that can be performed when right clicking on a graph or drag-releasing on a graph from a pin
	*
	* @param [in,out]	ContextMenuBuilder	The context (graph, dragged pin, etc...) and output menu builder.
	*/
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
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