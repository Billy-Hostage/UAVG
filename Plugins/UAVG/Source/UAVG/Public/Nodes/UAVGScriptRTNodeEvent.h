//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeEvent.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeEvent : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeEvent();
	
	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FString EventName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Arguments;
};