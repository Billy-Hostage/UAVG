//NTRHostage

#include "UAVGScriptRTNodeRunSubScript.h"

UUAVGScriptRuntimeNodeRunSubScript::UUAVGScriptRuntimeNodeRunSubScript()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeRunSubScript::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_RunSubScript);

	Response.SubScriptToRun = SubRTScript;

	return Response;
}
