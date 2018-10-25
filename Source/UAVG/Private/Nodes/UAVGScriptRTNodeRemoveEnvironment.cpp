//NTRHostage

#include "UAVGScriptRTNodeRemoveEnvironment.h"

UUAVGScriptRuntimeNodeRemoveEnvironment::UUAVGScriptRuntimeNodeRemoveEnvironment()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeRemoveEnvironment::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor);

	Response.EnvironmentsToRemove = EnvironmentsToRemove;

	return Response;
}
