//NTRHostage

#include "UAVGScriptGraph/Nodes/UAVGScriptGraphNodeSetWhiteboardVariable.h"
#include "UAVGScript.h"
#include "Nodes/UAVGScriptRTNodeSetWhiteboardVariable.h"

UUAVGScriptGraphNodeSetWhiteboardVariable::UUAVGScriptGraphNodeSetWhiteboardVariable(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

void UUAVGScriptGraphNodeSetWhiteboardVariable::SetupRTNode(class UUAVGScript* RTScript)
{
    check(RTScript != nullptr);
    if (MyRTNode == nullptr)
    {
        UUAVGScriptRTNodeSetWhiteboardVariable* RTNode = NewObject<UUAVGScriptRTNodeSetWhiteboardVariable>(RTScript);
        MyRTNode = CastChecked<UUAVGScriptRuntimeNode>(RTNode);
        if (MyRTNode != nullptr)
        {
            RTScript->AddRuntimeNode(MyRTNode);
        }
    }
}

void UUAVGScriptGraphNodeSetWhiteboardVariable::SaveToRTNode(class UUAVGScript* RTScript)
{
    Super::SaveToRTNode(RTScript);
    UUAVGScriptRTNodeSetWhiteboardVariable* RTEventNode = CastChecked<UUAVGScriptRTNodeSetWhiteboardVariable>(MyRTNode);

    RTEventNode->Key = Key;
    RTEventNode->Value = Value;
}

FText UUAVGScriptGraphNodeSetWhiteboardVariable::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    switch (TitleType)
    {
    case ENodeTitleType::FullTitle:
    case ENodeTitleType::MenuTitle:
    case ENodeTitleType::EditableTitle:
        return NSLOCTEXT("UAVGScriptGraphNode_SetWhiteboardVariable", "SetWhiteboardVariableList", "Set Variable");
    case ENodeTitleType::ListView:
    default:
        return NSLOCTEXT("UAVGScriptGraphNode_SetWhiteboardVariable", "SetWhiteboardVariableFullTitle", "Set Whiteboard Variable");
    }
}

void UUAVGScriptGraphNodeSetWhiteboardVariable::AllocateDefaultPins()
{
    CreateInputPin();
    CreateOutputPin();
}

void UUAVGScriptGraphNodeSetWhiteboardVariable::CreateOutputPin()
{
    const FName PinName(TEXT("Out"));
    FCreatePinParams PinParams;
    PinParams.Index = 1;

    CreatePin(EGPD_Output, FName(TEXT("ChildOutputs")), PinName, PinParams);
}

void UUAVGScriptGraphNodeSetWhiteboardVariable::CreateInputPin()
{
    const FName PinName(TEXT("In"));
    FCreatePinParams PinParams;
    PinParams.Index = 0;

    CreatePin(EGPD_Input, FName(TEXT("ParentInputs")), PinName, PinParams);
}