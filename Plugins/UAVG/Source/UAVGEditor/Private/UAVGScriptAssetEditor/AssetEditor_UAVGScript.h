//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "IUAVGScriptEditor.h"
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
private:
	class UUAVGScript* EditingScript;

	void CreateEditorGraph();

	/** IToolkit interface */
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

	/** Creates all internal widgets for the tabs to point at */
	void CreateInternalWidgets();

	TSharedRef<class SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);
	TSharedRef<class SDockTab> SpawnTab_Properties(const FSpawnTabArgs& Args);

	/** Create new graph editor widget */
	TSharedRef<class SGraphEditor> CreateGraphEditorWidget();

	/**	The tab ids for all the tabs used */
	static const FName GraphCanvasTabId;
	static const FName PropertiesTabId;

	/** Graph Editor */
	TSharedPtr<class SGraphEditor> GraphEditor;

	/** Property View */
	TSharedPtr<class IDetailsView> DetailsView;
};