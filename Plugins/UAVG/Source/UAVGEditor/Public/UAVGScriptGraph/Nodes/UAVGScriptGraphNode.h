//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "UAVGScriptGraphNode.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()

private:
	/** Pin that connects to all children */
	UEdGraphPin * ChildPin;
	/** Pin that connects to its parent */
	UEdGraphPin* ParentPin;
};