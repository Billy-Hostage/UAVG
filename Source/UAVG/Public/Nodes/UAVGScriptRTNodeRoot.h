//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRoot.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeRoot : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeRoot();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive() override;

	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FName ScriptName;

	UPROPERTY(BlueprintReadOnly)
	uint8 DefaultCharacterDisplayDelayInMs = 200;
};