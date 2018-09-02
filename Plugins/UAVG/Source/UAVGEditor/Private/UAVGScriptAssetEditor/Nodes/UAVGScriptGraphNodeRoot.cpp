//NTRHostage

#include "UAVGScriptGraphNodeRoot.h"

UUAVGScriptGraphNodeRoot::UUAVGScriptGraphNodeRoot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeRoot::AllocateDefaultPins()
{
	//We only have a output pin in root node
	CreateOutputPin();
}

void UUAVGScriptGraphNodeRoot::CreateOutputPin()
{
	static const FName PinName(TEXT("Begin"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;//Root Begin Pin at Array Index 0

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}
