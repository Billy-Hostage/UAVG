//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRunSubScript.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeRunSubScript : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeRunSubScript();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive() override;

	UPROPERTY(BlueprintReadOnly)
	class UUAVGScript* SubRTScript;
};
