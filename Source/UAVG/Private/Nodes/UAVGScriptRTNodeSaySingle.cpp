//NTRHostage

#include "Nodes/UAVGScriptRTNodeSaySingle.h"

UUAVGScriptRuntimeNodeSaySingle::UUAVGScriptRuntimeNodeSaySingle()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeSaySingle::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_Say);

	Response.DesiredTexts = SaySingleTextsArray;

	return Response;
}
