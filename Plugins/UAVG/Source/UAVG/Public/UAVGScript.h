//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "UAVGScript.generated.h"

class UUAVGScriptRuntimeNode;
class UUAVGScriptRuntimeNodeRoot;

//Main Script Data Asset Holder for UAVG Plugin
UCLASS(Blueprintable, BlueprintType)
class UAVG_API UUAVGScript : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScript();

	const UUAVGScriptRuntimeNodeRoot* GetConstRuntimeRootNode() const
	{
		return RootNode;
	};
	UUAVGScriptRuntimeNodeRoot* SetupNewRuntimeScript();

	bool AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode);

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	class UEdGraph* MyEdGraph;

#endif
protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General", meta = (DisplayName = "Script Name", ShortTooltip = "Name of Script", ToolTip = "The Name of This UAVG Script"))
	FName ScriptName;

	UPROPERTY(BlueprintReadOnly)
	UUAVGScriptRuntimeNodeRoot* RootNode;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UUAVGScriptRuntimeNode*> AllNodes;
};