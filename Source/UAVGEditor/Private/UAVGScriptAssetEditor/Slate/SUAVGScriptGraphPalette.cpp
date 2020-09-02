//NTRHostage

#include "UAVGScriptGraph/Slate/SUAVGScriptGraphPalette.h"
#include "UAVGScriptGraph/AssetGraphSchema_UAVGScript.h"

void SUAVGScriptGraphPalette::Construct(const FArguments& InArgs)
{
	// Auto expand the palette as there's so few nodes
	SGraphPalette::Construct(SGraphPalette::FArguments().AutoExpandActionMenu(true));
}

void SUAVGScriptGraphPalette::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
	const UAssetGraphSchema_UAVGScript* Schema = GetDefault<UAssetGraphSchema_UAVGScript>();
	FGraphActionMenuBuilder ActionMenuBuilder;
	Schema->GetPaletteActions(ActionMenuBuilder);
	OutAllActions.Append(ActionMenuBuilder);
}