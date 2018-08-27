//NTRHostage Coded

#include "AssetEditor_UAVGScript.h"
#include "EdGraph_UAVGScript.h"
#include "UAVGScript.h"

#define LOCTEXT_NAMESPACE "AssetEditor_GenericGraph"
DEFINE_LOG_CATEGORY(LogUAVGScriptAssetEditor);

const FName UAVGScriptEditorAppName = FName(TEXT("UAVGScriptEditorApp"));

FAssetEditor_UAVGScrpit::FAssetEditor_UAVGScrpit()
{
	EditingScript = nullptr;
}

FAssetEditor_UAVGScrpit::~FAssetEditor_UAVGScrpit()
{

}

void FAssetEditor_UAVGScrpit::InitUAVGScriptAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UUAVGScript* InScrpit)
{
	EditingScript = InScrpit;
	CreateEditorGraph();
}

void FAssetEditor_UAVGScrpit::CreateEditorGraph()
{
	if (EditingScript->MyEdGraph == nullptr)
	{
		//EditingScript->MyEdGraph = CastChecked<UEdGraph_UAVGScript>(TODO);
	}
}

#undef LOCTEXT_NAMESPACE