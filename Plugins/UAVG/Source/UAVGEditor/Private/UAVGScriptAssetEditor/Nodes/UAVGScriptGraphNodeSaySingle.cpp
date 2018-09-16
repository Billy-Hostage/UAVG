//NTRHostage

#include "UAVGScriptGraphNodeSaySingle.h"

UUAVGScriptGraphNodeSaySingle::UUAVGScriptGraphNodeSaySingle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FText UUAVGScriptGraphNodeSaySingle::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::ListView:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_SaySingle", "SaySingleList", "Say Single");
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_SaySingle", "SaySingleFullTitle", "Say Single Node");
	}
}

void UUAVGScriptGraphNodeSaySingle::AllocateDefaultPins()
{
	//We have both a output and input pin.
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeSaySingle::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeSaySingle::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
