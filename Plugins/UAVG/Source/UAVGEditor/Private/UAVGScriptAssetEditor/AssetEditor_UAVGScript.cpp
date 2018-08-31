//NTRHostage Coded

#include "AssetEditor_UAVGScript.h"

#include "EdGraph_UAVGScript.h"
#include "AssetGraphSchema_UAVGScript.h"
#include "UAVGScript.h"

#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "SUAVGScriptGraphPalette.h"

#include "Kismet2/BlueprintEditorUtils.h"
#include "GenericCommands.h"
#include "GraphEditorActions.h"
#include "Widgets/Docking/SDockTab.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "AssetEditor_GenericGraph"
DEFINE_LOG_CATEGORY(LogUAVGScriptAssetEditor);

const FName UAVGScriptEditorAppName = FName(TEXT("UAVGScriptEditorApp"));
const FName FAssetEditor_UAVGScrpit::GraphCanvasTabId(TEXT("UAVGScriptEditor_GraphCanvas"));
const FName FAssetEditor_UAVGScrpit::PropertiesTabId(TEXT("UAVGScriptEditor_Properties"));
const FName FAssetEditor_UAVGScrpit::PaletteTabId(TEXT("UAVGScriptEditor_Palette"));

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

	InTabManager->RegisterTabSpawner(GraphCanvasTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_UAVGScrpit::SpawnTab_GraphCanvas))
		.SetDisplayName(LOCTEXT("GraphCanvasTab", "Graph"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(PropertiesTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_UAVGScrpit::SpawnTab_Properties))
		.SetDisplayName(LOCTEXT("PropertiesTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	InTabManager->RegisterTabSpawner(PaletteTabId, FOnSpawnTab::CreateSP(this, &FAssetEditor_UAVGScrpit::SpawnTab_Palette))
		.SetDisplayName(LOCTEXT("PaletteTab", "Palette"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Palette"));
}

void FAssetEditor_UAVGScrpit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(GraphCanvasTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

void FAssetEditor_UAVGScrpit::InitUAVGScriptAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UUAVGScript* InScrpit)
{
	EditingScript = InScrpit;

	EditingScript->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	CreateEditorGraph();

	CreateInternalWidgets();
	
	TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_UAVGScriptEditor_Layout_v2")->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->SetHideTabWell(true)
			->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewSplitter()
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(PropertiesTabId, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab(GraphCanvasTabId, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(PaletteTabId, ETabState::OpenedTab)
			)
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, UAVGScriptEditorAppName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InScrpit, false);
}

void FAssetEditor_UAVGScrpit::PostUndo(bool bSuccess)
{
	//TODO Rearrange and save
}

void FAssetEditor_UAVGScrpit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(EditingScript);
}

void FAssetEditor_UAVGScrpit::CreateEditorGraph()
{
	if (EditingScript->MyEdGraph == nullptr)
	{
		EditingScript->MyEdGraph = CastChecked<UEdGraph_UAVGScript>(FBlueprintEditorUtils::CreateNewGraph(EditingScript, NAME_None, UEdGraph_UAVGScript::StaticClass(), UAssetGraphSchema_UAVGScript::StaticClass()));
		EditingScript->MyEdGraph->bAllowDeletion = false;
		const UEdGraphSchema* Schema = EditingScript->MyEdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*(EditingScript->MyEdGraph));
	}
}

FName FAssetEditor_UAVGScrpit::GetToolkitFName() const
{
	return FName("FUAVGScriptEditor");
}

FText FAssetEditor_UAVGScrpit::GetToolkitName() const
{
	const bool bDirtyState = EditingScript->GetOutermost()->IsDirty();

	FFormatNamedArguments Args;
	Args.Add(TEXT("UAVGScriptName"), FText::FromString(EditingScript->GetName()));
	Args.Add(TEXT("DirtyState"), bDirtyState ? FText::FromString(TEXT("*")) : FText::GetEmpty());
	return FText::Format(LOCTEXT("UAVGScriptToolkitName", "{UAVGScriptName}{DirtyState}"), Args);
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
	GraphEditor = CreateGraphEditorWidget();

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	const FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::ObjectsUseNameArea, false);
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(EditingScript);

	Palette = SNew(SUAVGScriptGraphPalette);
}

TSharedRef<SGraphEditor> FAssetEditor_UAVGScrpit::CreateGraphEditorWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_UAVGScriptGraph", "UAVG SCRIPT");
	AppearanceInfo.InstructionText = LOCTEXT("AppearanceInstructionText_UAVGScriptGraph", "Right Click to Add Nodes");

	SGraphEditor::FGraphEditorEvents InEvents;//TODO
	//InEvents.OnCreateActionMenu = SGraphEditor::FOnCreateActionMenu::CreateSP(this, &FAssetEditor_UAVGScrpit::OnCreateGraphActionMenu);

	return SNew(SGraphEditor)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(EditingScript->MyEdGraph)
		.GraphEvents(InEvents)
		.ShowGraphStateOverlay(false);
}

TSharedRef<SDockTab> FAssetEditor_UAVGScrpit::SpawnTab_GraphCanvas(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == GraphCanvasTabId);

	return SNew(SDockTab)
		.Label(LOCTEXT("UAVGScriptEditorGraphCanvasTitle", "Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}
TSharedRef<SDockTab> FAssetEditor_UAVGScrpit::SpawnTab_Properties(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
		.Label(LOCTEXT("UAVGScriptEditorPropertiesTitle", "Details"))
		[
			DetailsView.ToSharedRef()
		];
}
TSharedRef<SDockTab> FAssetEditor_UAVGScrpit::SpawnTab_Palette(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PaletteTabId);

	return SNew(SDockTab)
		.Icon(FEditorStyle::GetBrush("Kismet.Tabs.Palette"))
		.Label(LOCTEXT("UAVGScriptEditorGraphPaletteTitle", "Palette"))
		[
			Palette.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE