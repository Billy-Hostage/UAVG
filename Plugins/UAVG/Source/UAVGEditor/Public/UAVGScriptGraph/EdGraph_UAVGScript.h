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

	/**
	* Note that the object will be modified. If we are currently recording into the
	* transaction buffer (undo/redo), save a copy of this object into the buffer and
	* marks the package as needing to be saved.
	*
	* @param	bAlwaysMarkDirty	if true, marks the package dirty even if we aren't
	*								currently recording an active undo/redo transaction
	* @return true if the object was saved to the transaction buffer
	*/
	virtual bool Modify(bool bAlwaysMarkDirty = true) override;

	class UUAVGScriptGraphNode* CreateNode(TSubclassOf<UUAVGScriptGraphNode> NodeClass, int32 NodePosX, int32 NodePosY, bool bSelectNewNode = true, bool bIsUserAction = true);

	class UUAVGScript* GetUAVGScript() const;

	class UUAVGScriptGraphNodeRoot* GetRootNode();

	void RebulidRuntimeScript();
};