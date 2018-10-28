//NTRHostage

#include "UAVGScriptGraphNodeSaySingle.h"

#include "UAVGScript.h"
#include "UAVGScriptGraphPin.h"
#include "UAVGScriptRTNodeSaySingle.h"

UUAVGScriptGraphNodeSaySingle::UUAVGScriptGraphNodeSaySingle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeSaySingle::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeSaySingle* RTNode = NewObject<UUAVGScriptRuntimeNodeSaySingle>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeSaySingle::SaveToRTNode(UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeSaySingle* RTSaySingleNode = CastChecked<UUAVGScriptRuntimeNodeSaySingle>(MyRTNode);

	RTSaySingleNode->SaySingleTextsArray = SaySingleTextArray;
}

FText UUAVGScriptGraphNodeSaySingle::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	switch (TitleType)
	{
	case ENodeTitleType::FullTitle:
	case ENodeTitleType::MenuTitle:
	case ENodeTitleType::EditableTitle:
		return NSLOCTEXT("UAVGScriptGraphNode_SaySingle", "SaySingleList", "Say Single Line");
	case ENodeTitleType::ListView:
	default:
		return NSLOCTEXT("UAVGScriptGraphNode_SaySingle", "SaySingleFullTitle", "Say Single Line Node");
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
