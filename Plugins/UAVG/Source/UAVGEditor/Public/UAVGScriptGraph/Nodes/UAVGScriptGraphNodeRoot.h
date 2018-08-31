//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptGraphNode.h"
#include "UAVGScriptGraphNodeRoot.generated.h"

UCLASS(MinimalAPI)
class UUAVGScriptGraphNodeRoot : public UUAVGScriptGraphNode
{
	GENERATED_UCLASS_BODY()
public:
	bool IsUserCreatable() const override
	{
		return false;
	}

	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return NSLOCTEXT("UAVGScriptGraphNode_Root", "RootTitle", "Root");
	}

	FText GetTooltipText() const override
	{
		return NSLOCTEXT("UAVGScriptGraphNode_Root", "RootToolTip", "The root start node of this graph");
	}

	bool IsRootNode() const override
	{
		//This is a root node.
		return true;
	}
private:
protected:
	void CreateOutputPin() override;
};