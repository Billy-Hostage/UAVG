//NTRHostage

#include "SUAVGScriptGraphPalette.h"

void SUAVGScriptGraphPalette::Construct(const FArguments& InArgs)
{
	// Auto expand the palette as there's so few nodes
	SGraphPalette::Construct(SGraphPalette::FArguments().AutoExpandActionMenu(true));
}

void SUAVGScriptGraphPalette::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
	FGraphActionMenuBuilder ActionMenuBuilder;

	OutAllActions.Append(ActionMenuBuilder);
}