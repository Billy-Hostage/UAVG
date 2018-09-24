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

	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FName ScriptName;

	UPROPERTY(BlueprintReadOnly)
	uint8 CharacterDisplayDelayInMs = 200;
};