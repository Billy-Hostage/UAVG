//NTRHostage

#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNodeRunScriptText.h"
#include "UAVGScript.h"
#include "Nodes/UAVGScriptRTNodeRunScriptText.h"

UUAVGScriptGraphNodeRunScriptText::UUAVGScriptGraphNodeRunScriptText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeRunScriptText::SetupRTNode(class UUAVGScript* RTScript)
{
	check(RTScript != nullptr);
	if (MyRTNode == nullptr)
	{
		UUAVGScriptRuntimeNodeRunScriptText* RTNode = NewObject<UUAVGScriptRuntimeNodeRunScriptText>(RTScript);
		MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
		if (MyRTNode != nullptr)
		{
			RTScript->AddRuntimeNode(MyRTNode);
		}
	}
}

void UUAVGScriptGraphNodeRunScriptText::SaveToRTNode(class UUAVGScript* RTScript)
{
	Super::SaveToRTNode(RTScript);
	UUAVGScriptRuntimeNodeRunScriptText* RTNode = CastChecked<UUAVGScriptRuntimeNodeRunScriptText>(MyRTNode);

	RTNode->ScriptTextAsset = ScriptText;
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