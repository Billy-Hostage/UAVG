//NTRHostage

#include "UAVGScriptRTNodeSelection.h"

UUAVGScriptRuntimeNodeSelection::UUAVGScriptRuntimeNodeSelection()
{

}

bool UUAVGScriptRuntimeNodeSelection::EditorAddSelectionNodes(UUAVGScriptRuntimeNode* InNode)
{
	if(!CheckNodeCanBePaentOrChild(InNode))
	{
		return false;
	}
	SelectionNodes.Add(InNode);
	return true;
}
void UUAVGScriptRuntimeNodeSelection::EditorClearSelections()
{
	Selections.Empty();
	SelectionNodes.Empty();
}

UUAVGScriptRuntimeNode* UUAVGScriptRuntimeNodeSelection::GetNextNode(class UUAVGComponent* InComponent)
{
	if(SelectedIndexs.Contains(InComponent))
	{
		return SelectionNodes.IsValidIndex(SelectedIndexs[InComponent])? SelectionNodes[SelectedIndexs[InComponent]] : nullptr;
	}
	else
	{
		return SelectionNodes.IsValidIndex(DefaultIndex)? SelectionNodes[DefaultIndex] : nullptr;
	}
}

void UUAVGScriptRuntimeNodeSelection::SetSelectionIndex(int32 SelectionIndex, class UUAVGComponent* InComponent)
{
	if(!ensure(InComponent)) return;
	if(!Selections.IsValidIndex(SelectionIndex))
	{
		if(SelectionIndex >= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid SelectionIndex at Node %s"), *GetName());
		}
		SelectedIndexs.Add(InComponent, DefaultIndex);
	}
	SelectedIndexs.Add(InComponent, SelectionIndex);
}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeSelection::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_Selection);

	if(Selections.Num() != SelectionNodes.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selections and SelectionNodes Arrays are not alligned. %d != %d"), Selections.Num(), SelectionNodes.Num());
	}
	if(Selections.Num() == 0 || SelectionNodes.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Selections or SelectionNodes Arrays are empty. %d == 0 || %d == 0"), Selections.Num(), SelectionNodes.Num());
	}

	Response.SelectionTexts = Selections;

	return Response;
}

void UUAVGScriptRuntimeNodeSelection::OnLeave(class UUAVGComponent* InComponent)
{
	if(SelectedIndexs.Contains(InComponent))
	{
		SelectedIndexs.Remove(InComponent);
	}
	Super::OnLeave(InComponent);
}
