//NTRHostage

#include "UAVGScriptGraphNodeSelection.h"

#include "UAVGScriptGraphPin.h"

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
	Selections.Init(FText::GetEmpty(), 2);
	CreateInputPin();
	CreateOutputPins(1);
	CreateOutputPins(2);
}

void UUAVGScriptGraphNodeSelection::CreateOutputPins(int32 Index)
{
	if(!ensure(Index >= 1)) return;

	const FName PinName(*(FString::Printf(TEXT("Out%d"), Index)));
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

TArray<UEdGraphPin*> UUAVGScriptGraphNodeSelection::GetOutputPins()
{
	TArray<UEdGraphPin*> ToReturn;
	ToReturn = Pins;
	ToReturn.RemoveAt(0);
	return ToReturn;
}

//TODO Remove Magic Numbers
void UUAVGScriptGraphNodeSelection::PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName().ToString() == "Selections")
	{
		int32 ModifiedArrayIndex = PropertyChangedEvent.GetArrayIndex("Selections");
		if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd)
		{
			CreateOutputPins(ModifiedArrayIndex + 1);
			GetGraph()->NotifyGraphChanged();
		}
		else if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove)
		{
			RemovePinAt(ModifiedArrayIndex, EEdGraphPinDirection::EGPD_Output);
		}
		else if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear)
		{
			int32 OldOutPinNums = Pins.Num() - 1; //get rid of the input pin
			for(int32 i  = 0; i < OldOutPinNums; ++i)
			{
				RemovePinAt(0, EEdGraphPinDirection::EGPD_Output);//remove output pins one by one
			}
		}
		else if(PropertyChangedEvent.ChangeType == EPropertyChangeType::Duplicate)
		{
			CreateOutputPins(ModifiedArrayIndex);//TODO Strange Behaviour
			GetGraph()->NotifyGraphChanged();
		}
	}
	
	Super::PostEditChangeChainProperty(PropertyChangedEvent);
}
