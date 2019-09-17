//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"//Use struct FUAVGScriptRuntimeNodeArriveResponse
#include "UAVGTextScriptInterpreter.generated.h"

UCLASS()
class UUAVGTextScriptInterpreter : public UObject
{
	GENERATED_BODY()
public:
	UUAVGTextScriptInterpreter();

	void SetupInterpreter(class UUAVGScriptText* InScriptTextAsset);

	void OnArrive(FUAVGScriptRuntimeNodeArriveResponse& Response);

	bool IsScriptTextCompleted();
protected:
	UPROPERTY()
	class UUAVGScriptText* ScriptTextAsset = nullptr;

	UPROPERTY()
	uint32 TextLinePointer = 0;
};