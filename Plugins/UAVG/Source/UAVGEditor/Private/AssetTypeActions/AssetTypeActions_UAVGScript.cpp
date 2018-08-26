//NTRHostage Coded

#include "AssetTypeActions_UAVGScript.h"
#include "UAVGScript.h"

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

uint32 FAssetTypeActions_UAVGScript::GetCategories()
{
	return EAssetTypeCategories::Misc | MyAssetCategory;
}

#undef LOCTEXT_NAMESPACE