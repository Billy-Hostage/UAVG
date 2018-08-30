//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeRoot.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeRoot : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()

private:
protected:
	virtual void CreateOutputPin() override;
};