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
	FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent) override;

	UUAVGScriptRuntimeNodeEvent();

	virtual bool UnWarpUAVGSaveGame(UUAVGComponent* InComponent, UUAVGSaveGame* InSave) override { return bIsCosmetic; /* prevent multiple execution or not depends on the bIsCosmetic flag*/ }
	
	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FString EventName;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> Arguments;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCosmetic = false;
};