//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "IUAVGScriptEditor.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGScriptAssetEditor, Log, All);

class FAssetEditor_UAVGScrpit : public IUAVGScriptEditor
{
public:
	FAssetEditor_UAVGScrpit();
	virtual ~FAssetEditor_UAVGScrpit();

	void InitUAVGScriptAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, class UUAVGScript* InScrpit);
private:
	class UUAVGScript* EditingScript;

	void CreateEditorGraph();
};