//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeSelection.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeSelection : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeSelection();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive() override;

	virtual UUAVGScriptRuntimeNode* GetNextNode(class UUAVGComponent* InComponent = nullptr) override;

	///These Arrays are alligned
	UPROPERTY(BlueprintReadOnly)
	TArray<FText> Selections;
	UPROPERTY(BlueprintReadOnly)
	TArray<UUAVGScriptRuntimeNode*> SelectionNodes;

	bool EditorAddSelectionNodes(UUAVGScriptRuntimeNode* InNode);
	void EditorClearSelections();

	//Transient Array to store SelectedIndexs, in case many UAVGComponent are using this node.
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<class UUAVGComponent*, int32> SelectedIndexs;
};
