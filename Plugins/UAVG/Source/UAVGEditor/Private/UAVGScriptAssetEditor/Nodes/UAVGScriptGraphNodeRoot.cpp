//NTRHostage

#include "UAVGScriptGraphNodeRoot.h"

#include "UAVGScript.h"
#include "UAVGScriptGraphNode.h"

UUAVGScriptGraphNodeRoot::UUAVGScriptGraphNodeRoot(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeRoot::SaveToRTNode(UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	//TODO
}

void UUAVGScriptGraphNodeRoot::AllocateDefaultPins()
{
	//We only have a output pin in root node
	CreateOutputPin();
}

void UUAVGScriptGraphNodeRoot::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
		MyRTNode = RTScript->SetupNewRuntimeScript();
}

void UUAVGScriptGraphNodeRoot::CreateOutputPin()
{
	const FName PinName(TEXT("Begin"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;//Root Begin Pin at Array Index 0

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}
