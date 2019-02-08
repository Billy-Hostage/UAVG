//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRoot.generated.h"

//Every UAVGScript has this root node
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
	int32 DefaultCharacterDisplayDelayInMs = 200;
};
