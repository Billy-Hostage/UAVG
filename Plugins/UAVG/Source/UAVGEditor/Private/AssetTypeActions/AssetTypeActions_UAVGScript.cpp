//NTRHostage Coded

#include "AssetTypeActions_UAVGScript.h"
#include "UAVGScript.h"
#include "AssetEditor_UAVGScript.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_UAVGScript"

FAssetTypeActions_UAVGScript::FAssetTypeActions_UAVGScript(EAssetTypeCategories::Type InAssetCategory)
	:MyAssetCategory(InAssetCategory)
{

}

FText FAssetTypeActions_UAVGScript::GetName() const
{
	return LOCTEXT("FUAVGScriptAssetTypeActionsName", "UAVG Script");
}

FColor FAssetTypeActions_UAVGScript::GetTypeColor() const
{
	return FColor(220, 20, 60);
}

UClass* FAssetTypeActions_UAVGScript::GetSupportedClass() const
{
	return UUAVGScript::StaticClass();
}

void FAssetTypeActions_UAVGScript::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	UUAVGScript* ScriptToEditPtr = nullptr;

	for (auto ObjectItr = InObjects.CreateConstIterator(); ObjectItr; ++ObjectItr)
	{
		ScriptToEditPtr = CastChecked<UUAVGScript>(*ObjectItr);
		if (ScriptToEditPtr && ScriptToEditPtr->IsValidLowLevel())
		{
			TSharedRef<FAssetEditor_UAVGScrpit> EditorNew(new FAssetEditor_UAVGScrpit());
			EditorNew->InitUAVGScriptAssetEditor(Mode, EditWithinLevelEditor, ScriptToEditPtr);
		}
	}
}

uint32 FAssetTypeActions_UAVGScript::GetCategories()
{
	return EAssetTypeCategories::Misc | MyAssetCategory;
}

#undef LOCTEXT_NAMESPACE