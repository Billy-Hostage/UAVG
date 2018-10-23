//NTRHostage

#include "UAVGScriptGraphNodeAddEnvironment.h"

#include "UAVGScriptGraphPin.h"
#include "UAVGScriptRTNodeAddEnvironment.h"

UUAVGScriptGraphNodeAddEnvironment::UUAVGScriptGraphNodeAddEnvironment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeAddEnvironment::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeAddEnvironment* RTNode = NewObject<UUAVGScriptRuntimeNodeAddEnvironment>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeAddEnvironment::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeAddEnvironment* RTAddEnvNode = CastChecked<UUAVGScriptRuntimeNodeAddEnvironment>(MyRTNode);
	
	RTAddEnvNode->EnvironmentToAdd = EnvironmentToAdd;
	RTAddEnvNode->AdditonalArguments = AdditonalArguments;
}

FText UUAVGScriptGraphNodeAddEnvironment::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::ListView:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_AddEnvironment", "AddEnvironmentList", "Add Environment Descriptor");
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_AddEnvironment", "AddEnvironmentFullTitle", "Add Environment Descriptor Node");
	}
}

void UUAVGScriptGraphNodeAddEnvironment::AllocateDefaultPins()
{
	//We have both a output and input pin.
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeAddEnvironment::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeAddEnvironment::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
