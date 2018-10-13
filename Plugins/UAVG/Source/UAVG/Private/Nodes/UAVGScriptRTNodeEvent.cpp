//NTRHostage

#include "UAVGScriptRTNodeEvent.h"

UUAVGScriptRuntimeNodeEvent::UUAVGScriptRuntimeNodeEvent()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeEvent::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_CustomEvent);
	Response.EventName = EventName;
	Response.EventArguments = Arguments;

	return Response;
}
