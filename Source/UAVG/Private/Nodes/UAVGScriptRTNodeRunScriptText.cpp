//NTRHostage

#include "UAVGScriptRTNodeRunScriptText.h"
#include "UAVGTextScriptInterpreter.h"

UUAVGScriptRuntimeNodeRunScriptText::UUAVGScriptRuntimeNodeRunScriptText()
{

}

FUAVGScriptRuntimeNodeArriveResponse UUAVGScriptRuntimeNodeRunScriptText::OnArrive(class UUAVGComponent* InComponent)
{
	FUAVGScriptRuntimeNodeArriveResponse Response;

	if (ScriptTextAsset == nullptr)
	{
		Response.NodeType = EUAVGRuntimeNodeType::URNT_NULL;
		return Response;
	}
	UUAVGTextScriptInterpreter* MyInterpreter = Interpreters.FindRef(InComponent);
	if (MyInterpreter == nullptr)
	{
		MyInterpreter = NewObject<UUAVGTextScriptInterpreter>();
		Interpreters.Add(InComponent, MyInterpreter);
		MyInterpreter->SetupInterpreter(ScriptTextAsset);
	}
	MyInterpreter->OnArrive(Response);//Pass-through Request
	return Response;
}

UUAVGScriptRuntimeNode* UUAVGScriptRuntimeNodeRunScriptText::GetNextNode(class UUAVGComponent* InComponent)
{
	UUAVGTextScriptInterpreter* MyInterpreter = Interpreters.FindRef(InComponent);
	if (MyInterpreter == nullptr || MyInterpreter->IsScriptTextCompleted())
		return Super::GetNextNode(InComponent);

	return this;
}