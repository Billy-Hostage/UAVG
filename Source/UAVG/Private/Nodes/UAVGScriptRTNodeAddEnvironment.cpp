//NTRHostage

#include "Nodes/UAVGScriptRTNodeAddEnvironment.h"

UUAVGScriptRuntimeNodeAddEnvironment::UUAVGScriptRuntimeNodeAddEnvironment()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeAddEnvironment::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor);

	Response.EnvironmentToAdd = EnvironmentToAdd;
	Response.AdditonalEnvironmentArguments = AdditonalArguments;

	return Response;
}
