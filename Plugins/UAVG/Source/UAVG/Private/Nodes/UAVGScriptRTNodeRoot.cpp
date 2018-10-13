//NTRHostage

#include "UAVGScriptRTNodeRoot.h"

UUAVGScriptRuntimeNodeRoot::UUAVGScriptRuntimeNodeRoot()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeRoot::OnArrive()
{
	UE_LOG(LogTemp, Error, TEXT("We should NEVER arrive at a RootNode %s !"), *GetName());

	return FUAVGScriptRuntimeNodeArriveResponse(EUAVGRuntimeNodeType::URNT_Root);
}
