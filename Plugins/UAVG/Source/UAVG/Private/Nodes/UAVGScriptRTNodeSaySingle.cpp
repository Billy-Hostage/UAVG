//NTRHostage

#include "UAVGScriptRTNodeSaySingle.h"

UUAVGScriptRuntimeNodeSaySingle::UUAVGScriptRuntimeNodeSaySingle()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeSaySingle::OnArrive()
{
	FUAVGScriptRuntimeNodeArriveResponse Response;
	Response.bShouldUpdateDesiredTexts = true;
	Response.DesiredTexts = SaySingleTextsArray;
	return Response;
}
