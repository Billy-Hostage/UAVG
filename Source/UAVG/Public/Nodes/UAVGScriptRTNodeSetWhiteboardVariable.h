//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeSetWhiteboardVariable.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRTNodeSetWhiteboardVariable : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent) override;

	UUAVGScriptRTNodeSetWhiteboardVariable();
	
	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FString Key;

	UPROPERTY(BlueprintReadOnly)
	FString Value;
};