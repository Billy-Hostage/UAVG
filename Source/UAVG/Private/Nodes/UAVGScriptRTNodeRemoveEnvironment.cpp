//NTRHostage

#include "UAVGScriptRTNodeRemoveEnvironment.h"

UUAVGScriptRuntimeNodeRemoveEnvironment::UUAVGScriptRuntimeNodeRemoveEnvironment()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeRemoveEnvironment::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor);

	Response.EnvironmentsToRemove = EnvironmentsToRemove;

	return Response;
}
