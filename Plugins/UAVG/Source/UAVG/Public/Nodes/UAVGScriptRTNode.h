//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.h"
#include "UAVGScriptRTNode.generated.h"

struct FUAVGScriptRuntimeNodeArriveResponse
{
public:
	bool bShouldUpdateDesiredTexts = false;
	TArray<FUAVGText> DesiredTexts;
};

UCLASS(Abstract, BlueprintType)
class UAVG_API UUAVGScriptRuntimeNode : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNode();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive()
	{
		return FUAVGScriptRuntimeNodeArriveResponse();
	}
	virtual UUAVGScriptRuntimeNode* GetNextNode();

	/*Called When Editor Saving Graph*/
	virtual bool SetChild(TArray<UUAVGScriptRuntimeNode*> InChildNodes);
	virtual bool SetParent(TArray<UUAVGScriptRuntimeNode*> InParentNodes);
	bool CheckNodeCanBePaentOrChild(UUAVGScriptRuntimeNode* InNode) const;
	/*End Called When Editor Saving Graph*/
public:
	UPROPERTY()
		TArray<UUAVGScriptRuntimeNode*> MyParentNodes;
	UPROPERTY()
		TArray<UUAVGScriptRuntimeNode*> MyChildNodes;
};