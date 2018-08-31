//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.generated.h"

UCLASS(Abstract, BlueprintType)
class UUAVGScriptRuntimeNode : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNode();

	UPROPERTY()
	TArray<UUAVGScriptRuntimeNode*> MyParentNodes;
	UPROPERTY()
	TArray<UUAVGScriptRuntimeNode*> MyChildNodes;

#if WITH_EDITORONLY_DATA
	/*Called When Editor Saving Graph*/
	virtual void SetChild(TArray<UUAVGScriptRuntimeNode*> InChildNodes);
	virtual void SetParent(TArray<UUAVGScriptRuntimeNode*> InParentNodes);
	bool CheckNodeCanBePaentOrChild(UUAVGScriptRuntimeNode* InNode) const;
	/*End Called When Editor Saving Graph*/

	class UUAVGScriptGraphNode* MyEditorNode = nullptr;
#endif
};