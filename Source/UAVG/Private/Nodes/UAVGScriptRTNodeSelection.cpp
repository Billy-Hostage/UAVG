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
	return nullptr; //TODO
}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeSelection::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor);

	//TODO

	return Response;
}
