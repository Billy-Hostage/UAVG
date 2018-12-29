//NTRHostage

#include "UAVGScriptGraphPin.h"
#include "UUAVGScriptGraphNodeSelection.h"

UUAVGScriptGraphNodeSelection::UUAVGScriptGraphNodeSelection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeSelection::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		//TODO
		//UUAVGScriptRuntimeNodeAddEnvironment* RTNode = NewObject<UUAVGScriptRuntimeNodeAddEnvironment>(RTScript);
		//MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		//if (MyRTNode != nullptr)
		//{
			//RTScript->AddRuntimeNode(MyRTNode);
		//}
	}
}

void UUAVGScriptGraphNodeSelection::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	//TODO
	//UUAVGScriptRuntimeNodeAddEnvironment* RTAddEnvNode = CastChecked<UUAVGScriptRuntimeNodeAddEnvironment>(MyRTNode);
	
	//RTAddEnvNode->EnvironmentToAdd = EnvironmentToAdd;
	//RTAddEnvNode->AdditonalArguments = AdditonalArguments;
}

FText UUAVGScriptGraphNodeSelection::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_Selection", "SelectionList", "Selection");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_Selection", "SelectionFullTitle", "Selection Node");
	}
}

void UUAVGScriptGraphNodeSelection::AllocateDefaultPins()
{
	//We have both a output and input pin.
	CreateInputPin();
	CreateOutputPin(1);
}

void UUAVGScriptGraphNodeSelection::CreateOutputPin(int32 Index)
{
	if(!ensure(Index >= 1)) return;

	const FName PinName(*(FString::Format("Out%d", Index)));
	FCreatePinParams PinParams;
	PinParams.Index = Index;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeSelection::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
