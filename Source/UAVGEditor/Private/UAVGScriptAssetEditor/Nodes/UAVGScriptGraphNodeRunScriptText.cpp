//NTRHostage

#include "UAVGScriptGraphNodeRunScriptText.h"

UUAVGScriptGraphNodeRunScriptText::UUAVGScriptGraphNodeRunScriptText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UUAVGScriptGraphNodeRunScriptText::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_RunScriptText", "RunScriptTextList", "Run Script Text");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_RunScriptText", "RunScriptTextFullTitle", "Run Script Text Node");
	}
}

void UUAVGScriptGraphNodeRunScriptText::AllocateDefaultPins()
{
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeRunScriptText::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeRunScriptText::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}