//NTRHostage

#include "UAVGScriptRTNodeSaySingle.h"

UUAVGScriptRuntimeNodeSaySingle::UUAVGScriptRuntimeNodeSaySingle()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeSaySingle::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response(EUAVGRuntimeNodeType::URNT_Say);

	Response.DesiredTexts = SaySingleTextsArray;

	return Response;
}
