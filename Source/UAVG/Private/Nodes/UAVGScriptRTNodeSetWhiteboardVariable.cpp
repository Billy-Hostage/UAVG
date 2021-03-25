//NTRHostage

#include "Nodes/UAVGScriptRTNodeSetWhiteboardVariable.h"

UUAVGScriptRTNodeSetWhiteboardVariable::UUAVGScriptRTNodeSetWhiteboardVariable()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRTNodeSetWhiteboardVariable::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_SetWhiteboardVar);
	Response.Key = Key;
	Response.Value = Value;

	return Response;
}
