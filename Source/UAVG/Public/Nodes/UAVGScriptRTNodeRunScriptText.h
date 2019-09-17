//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRunScriptText.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeRunScriptText : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeRunScriptText();

	FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent);

	UPROPERTY(BlueprintReadOnly)
	class UUAVGScriptText* ScriptTextAsset;

	virtual UUAVGScriptRuntimeNode* GetNextNode(class UUAVGComponent* InComponent = nullptr) override;
protected:
	UPROPERTY(BlueprintReadOnly)
	TMap<class UUAVGComponent*, class UUAVGTextScriptInterpreter*> Interpreters;
};