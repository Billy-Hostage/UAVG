//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeAddEnvironment.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeAddEnvironment : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeAddEnvironment();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive() override;

	UPROPERTY(BlueprintReadOnly)
	FString EnvironmentToAdd;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> AdditonalArguments;
};
