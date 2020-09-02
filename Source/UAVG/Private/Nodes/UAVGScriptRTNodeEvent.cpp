//NTRHostage

#include "Nodes/UAVGScriptRTNodeEvent.h"

UUAVGScriptRuntimeNodeEvent::UUAVGScriptRuntimeNodeEvent()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeEvent::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_CustomEvent);
	Response.EventName = EventName;
	Response.EventArguments = Arguments;

	return Response;
}
