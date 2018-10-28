//NTRHostage

#include "UAVGScriptGraphNodeEvent.h"

#include "UAVGScript.h"
#include "UAVGScriptRTNodeEvent.h"

UUAVGScriptGraphNodeEvent::UUAVGScriptGraphNodeEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeEvent::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeEvent* RTNode = NewObject<UUAVGScriptRuntimeNodeEvent>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeEvent::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeEvent* RTEventNode = CastChecked<UUAVGScriptRuntimeNodeEvent>(MyRTNode);

	RTEventNode->EventName = EventName;
	RTEventNode->Arguments = Arguments;
}

FText UUAVGScriptGraphNodeEvent::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_Event", "EventList", "Trigger Event");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_Event", "EventFullTitle", "Trigger Event Node");
	}
}

void UUAVGScriptGraphNodeEvent::AllocateDefaultPins()
{
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeEvent::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeEvent::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
