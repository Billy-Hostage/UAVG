//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "IUAVGScriptEditor.h"
#include "GraphEditor.h"
#include "EditorUndoClient.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGScriptAssetEditor, Log, All);

class FAssetEditor_UAVGScrpit : public IUAVGScriptEditor, public FEditorUndoClient, public FGCObject
{
public:
	FAssetEditor_UAVGScrpit();
	virtual ~FAssetEditor_UAVGScrpit();

	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;

	void InitUAVGScriptAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, class UUAVGScript* InScrpit);

	/** FEditorUndoClient Interface */
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override
	{
		PostUndo(bSuccess);
	}

	/** FGCObject interface */
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	//Begin Own Functions
	void SetDetailsViewTarget(class UObject* Target) const;

	void OnSelectionChanged(const FGraphPanelSelectionSet& SelectionSet) const;

	TSharedPtr<SGraphEditor> GetCurrentGraphEditor() const;
private:
	class UUAVGScript* EditingScript;
	
	void TryCreateEditorGraph();

	void BindEditorCommands();

	void DeleteSelectedNodes() const;
	bool CanDeleteNodes() const;
	void DuplicateNodes();
	bool CanDuplicateNodes();
	void CopySelectedNodes();
	bool CanCopyNodes();
	void PasteNodes();
	void PasteNodesAt(const FVector2D& Location);
	bool CanPasteNodes();
	void CutSelectedNodes();
	bool CanCutNodes();

	FGraphPanelSelectionSet GetSelectedNodes() const;
	
	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual void SaveAsset_Execute() override;

	/** Creates all internal widgets for the tabs to point at */
	void CreateInternalWidgets();

	TSharedRef<class SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnTab_Palette(const FSpawnTabArgs& Args);

	/** Create new graph editor widget */
	TSharedRef<class SGraphEditor> CreateGraphEditorWidget();

	virtual void RebuildRuntimeScript();
	virtual void RefreshUAVGEditor() const;

	/**	The tab ids for all the tabs used */
	static const FName GraphCanvasTabId;
	static const FName PropertiesTabId;
	static const FName PaletteTabId;

	/** Graph Editor */
	TSharedPtr<class SGraphEditor> GraphEditor;

	/** Property View */
	TSharedPtr<class IDetailsView> DetailsView;

	/** Palette of Sound Node types */
	TSharedPtr<class SUAVGScriptGraphPalette> Palette;

	TSharedPtr<FUICommandList> GraphEditorCommands;
};