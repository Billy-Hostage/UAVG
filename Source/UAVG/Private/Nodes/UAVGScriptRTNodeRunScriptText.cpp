//NTRHostage

#include "Nodes/UAVGScriptRTNodeRunScriptText.h"
#include "UAVGTextScriptInterpreter.h"
#include "UAVGSaveGame.h"

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

void UUAVGScriptRuntimeNodeRunScriptText::WarpUAVGSaveGame(class UUAVGComponent* InComponent, class UUAVGSaveGame* InSave)
{
	UUAVGTextScriptInterpreter* MyInterpreter = Interpreters.FindRef(InComponent);
	if (!ensure(MyInterpreter))
		return;

	MyInterpreter->WarpUAVGSaveGame(InSave);
}

bool UUAVGScriptRuntimeNodeRunScriptText::UnWarpUAVGSaveGame(UUAVGComponent* InComponent, UUAVGSaveGame* InSave)
{
	if (!ensure(InComponent && InSave))
		return true;
	if (!ensure(InSave->UsingScriptTextAsset == ScriptTextAsset))
		return true;

	UUAVGTextScriptInterpreter* MyInterpreter = NewObject<UUAVGTextScriptInterpreter>();
	Interpreters.Add(InComponent, MyInterpreter);
	MyInterpreter->UnWarpUAVGSaveGame(InSave);
	return true;
}
