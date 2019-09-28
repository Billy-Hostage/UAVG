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

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent) override;
	virtual void OnLeave(class UUAVGComponent* InComponent) override;
	virtual UUAVGScriptRuntimeNode* GetNextNode(class UUAVGComponent* InComponent = nullptr) override;

	virtual void SetSelectionIndex(int32 SelectionIndex, class UUAVGComponent* InComponent);

	///These Arrays are alligned
	UPROPERTY(BlueprintReadOnly)
	TArray<FText> Selections;
	UPROPERTY(BlueprintReadOnly)
	TArray<UUAVGScriptRuntimeNode*> SelectionNodes;

	UPROPERTY(BlueprintReadOnly)
	int32 DefaultIndex = 0;

	bool EditorAddSelectionNodes(UUAVGScriptRuntimeNode* InNode);
	void EditorClearSelections();

	//Transient Array to store SelectedIndexs, in case many UAVGComponent are using this node.
	UPROPERTY(BlueprintReadOnly, Transient)
	TMap<class UUAVGComponent*, int32> SelectedIndexs;
};
