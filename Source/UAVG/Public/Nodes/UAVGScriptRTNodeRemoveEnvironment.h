//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRemoveEnvironment.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeRemoveEnvironment : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeRemoveEnvironment();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent) override;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> EnvironmentsToRemove;
};
