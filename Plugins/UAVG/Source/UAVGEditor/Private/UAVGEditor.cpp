// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UAVGEditor.h"
#include "AssetTypeActions_UAVGScript.h"
#include "Slate/SUAVGScriptGraphNode.h"
#include "UAVGScriptGraphNode.h"

#include "EdGraphUtilities.h"

#define LOCTEXT_NAMESPACE "FUAVGEditorModule"

class FGraphPanelNodeFactory_UAVGScriptGraphNode : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UUAVGScriptGraphNode* UASNode = Cast<UUAVGScriptGraphNode>(Node))
		{
			UE_LOG(LogTemp, Warning, TEXT("Creating %s Slate UI"), *UASNode->GetName())
			return SNew(SUAVGScriptGraphNode, UASNode);
		}
		return nullptr;
	}
};

TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_UAVGScriptNode;

void FUAVGEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	GraphPanelNodeFactory_UAVGScriptNode = MakeShareable(new FGraphPanelNodeFactory_UAVGScriptGraphNode());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_UAVGScriptNode);

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	auto UAVGScriptCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UAVGScrpit")), LOCTEXT("UAVGScriptAssetCategory", "UAVGScript"));
	RegisterAssetTypeActions(AssetTools, MakeShareable(new FAssetTypeActions_UAVGScript(UAVGScriptCategoryBit)));
}

void FUAVGEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_UAVGScriptNode);
}

void FUAVGEditorModule::RegisterAssetTypeActions(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUAVGEditorModule, UAVGEditor)