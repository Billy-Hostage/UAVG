//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGText.h"
#include "UAVGScriptRTNodeSaySingle.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeSaySingle : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeSaySingle();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive() override;

	UPROPERTY(BlueprintReadOnly)
	TArray<FUAVGText> SaySingleTextsArray;
};
