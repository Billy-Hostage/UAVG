//NTRHostage

#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNodeRunSubScript.h"

#include "UAVGScriptGraph/Slate/SUAVGScriptGraphPin.h"
#include "Nodes/UAVGScriptRTNodeRunSubScript.h"

UUAVGScriptGraphNodeRunSubScript::UUAVGScriptGraphNodeRunSubScript(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeRunSubScript::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeRunSubScript* RTNode = NewObject<UUAVGScriptRuntimeNodeRunSubScript>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeRunSubScript::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeRunSubScript* RTRunSubScriptNode = CastChecked<UUAVGScriptRuntimeNodeRunSubScript>(MyRTNode);
	
	RTRunSubScriptNode->SubRTScript = SubRTScript;
}

FText UUAVGScriptGraphNodeRunSubScript::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_RunSubScript", "RunSubScriptList", "Run SubScript");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_RunSubScript", "RunSubScriptFullTitle", "Add Run SubScript Node");
	}
}

void UUAVGScriptGraphNodeRunSubScript::AllocateDefaultPins()
{
	//We have both a output and input pin.
	CreateInputPin();
	CreateOutputPin();
}

void UUAVGScriptGraphNodeRunSubScript::CreateOutputPin()
{
	const FName PinName(TEXT("Out"));
	FCreatePinParams PinParams;
	PinParams.Index = 1;

	CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeRunSubScript::CreateInputPin()
{
	const FName PinName(TEXT("In"));
	FCreatePinParams PinParams;
	PinParams.Index = 0;

	CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}
