//NTRHostage

#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNodeRemoveEnvironment.h"

#include "UAVGScriptGraph/Slate/SUAVGScriptGraphPin.h"
#include "Nodes/UAVGScriptRTNodeRemoveEnvironment.h"

UUAVGScriptGraphNodeRemoveEnvironment::UUAVGScriptGraphNodeRemoveEnvironment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeRemoveEnvironment::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeRemoveEnvironment* RTNode = NewObject<UUAVGScriptRuntimeNodeRemoveEnvironment>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeRemoveEnvironment::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeRemoveEnvironment* RTRemEnvNode = CastChecked<UUAVGScriptRuntimeNodeRemoveEnvironment>(MyRTNode);
	
	RTRemEnvNode->EnvironmentsToRemove = EnvironmentsToRemove;
}

FText UUAVGScriptGraphNodeRemoveEnvironment::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_RemoveEnvironment", "RemoveEnvironmentList", "Remove Environment Descriptor");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_RemoveEnvironment", "RemoveEnvironmentFullTitle", "Remove Environment Descriptor Node");
	}
}

void UUAVGScriptGraphNodeRemoveEnvironment::AllocateDefaultPins()
{
	//We have both a output and input pin.
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeRemoveEnvironment::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeRemoveEnvironment::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
