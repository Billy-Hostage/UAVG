//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_UAVGScript.generated.h"

UCLASS()
class UEdGraph_UAVGScript : public UEdGraph
{
	GENERATED_BODY()
public:
	UEdGraph_UAVGScript();
	virtual ~UEdGraph_UAVGScript();

	virtual bool Modify(bool bAlwaysMarkDirty = true) override;

	class UUAVGScriptGraphNode* CreateNode(TSubclassOf<UUAVGScriptGraphNode> NodeClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true, bool bIsUserAction = true);

	class UUAVGScript* GetUAVGScript() const;

	class UUAVGScriptGraphNodeRoot* GetRootNode();

	void RebulidRuntimeScript();
};