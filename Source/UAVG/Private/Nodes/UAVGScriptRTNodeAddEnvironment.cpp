//NTRHostage

#include "UAVGScriptRTNodeAddEnvironment.h"

UUAVGScriptRuntimeNodeAddEnvironment::UUAVGScriptRuntimeNodeAddEnvironment()
{

}
<<<<<<< HEAD

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeAddEnvironment::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor);

	Response->EnvironmentToAdd = EnvironmentToAdd;
	Response->AdditonalEnvironmentArguments = AdditonalArguments;

	return Response;
}
=======
>>>>>>> dev-env
