//NTRHostage Coded

#include "AssetEditor_UAVGScript.h"

#include "EdGraph_UAVGScript.h"
#include "AssetGraphSchema_UAVGScript.h"
#include "UAVGScript.h"

#include "Kismet2/BlueprintEditorUtils.h"
#include "GenericCommands.h"
#include "GraphEditorActions.h"

#define LOCTEXT_NAMESPACE "AssetEditor_GenericGraph"
DEFINE_LOG_CATEGORY(LogUAVGScriptAssetEditor);

const FName UAVGScriptEditorAppName = FName(TEXT("UAVGScriptEditorApp"));
const FName FAssetEditor_UAVGScrpit::GraphCanvasTabId(TEXT("UAVGScriptEditor_GraphCanvas"));
const FName FAssetEditor_UAVGScrpit::PropertiesTabId(TEXT("UAVGScriptEditor_Properties"));

FAssetEditor_UAVGScrpit::FAssetEditor_UAVGScrpit()
{
	EditingScript = nullptr;
}

FAssetEditor_UAVGScrpit::~FAssetEditor_UAVGScrpit()
{

}

void FAssetEditor_UAVGScrpit::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_UAVGScriptEditor", "UAVG Script Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	//TODO Register tabs here
}

void FAssetEditor_UAVGScrpit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	//TODO Unregister tabs here
}

void FAssetEditor_UAVGScrpit::InitUAVGScriptAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UUAVGScript* InScrpit)
{
	EditingScript = InScrpit;

	//EditingScript->SetFlags(RF_Transactional);
	//GEditor->RegisterForUndo(this);

	CreateEditorGraph();

	CreateInternalWidgets();
	
	//TODO Slate Style

	//FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, UAVGScriptEditorAppName, TODOLayout, true, true, InScrpit, false);
}

void FAssetEditor_UAVGScrpit::PostUndo(bool bSuccess)
{
	//TODO Rearrange and save
}

void FAssetEditor_UAVGScrpit::CreateEditorGraph()
{
	if (EditingScript->MyEdGraph == nullptr)
	{
		EditingScript->MyEdGraph = CastChecked<UEdGraph_UAVGScript>(FBlueprintEditorUtils::CreateNewGraph(EditingScript, NAME_None, UEdGraph_UAVGScript::StaticClass(), UAssetGraphSchema_UAVGScript::StaticClass()));
	}
}

FName FAssetEditor_UAVGScrpit::GetToolkitFName() const
{
	return FName("FUAVGScriptEditor");
}

FText FAssetEditor_UAVGScrpit::GetBaseToolkitName() const
{
	return LOCTEXT("UAVGScriptEditorAppLabel", "UAVG Script Editor");
}

FLinearColor FAssetEditor_UAVGScrpit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FAssetEditor_UAVGScrpit::GetWorldCentricTabPrefix() const
{
	return TEXT("UAVGScriptEditor");
}

void FAssetEditor_UAVGScrpit::CreateInternalWidgets()
{
	//TODO SGraphEditor
}

//TSharedRef<SGraphEditor> FAssetEditor_UAVGScrpit::CreateGraphEditorWidget()
//{
//	
//}

#undef LOCTEXT_NAMESPACE