//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeSaySingle.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeSaySingle : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeSaySingle();

	UPROPERTY(BlueprintReadOnly)
	TArray<FText> SaySingleTextsArray;

	UPROPERTY(BlueprintReadOnly)
	TArray<uint8> DisplayCharacterDelayInMs;
};