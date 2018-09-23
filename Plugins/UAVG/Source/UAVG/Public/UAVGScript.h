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
	UPROPERTY(BlueprintReadOnly)
	UUAVGScriptRuntimeNodeRoot* RootNode;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UUAVGScriptRuntimeNode*> AllNodes;
};