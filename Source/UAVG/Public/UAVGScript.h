//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "UAVGScript.generated.h"

class UUAVGScriptRuntimeNode;
class UUAVGScriptRuntimeNodeRoot;

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGRuntimeScript, Log, All);

//Main Script Data Asset Holder for UAVG Plugin
UCLASS(Blueprintable, BlueprintType)
class UAVG_API UUAVGScript : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScript();
	
	UUAVGScriptRuntimeNodeRoot* GetRuntimeRootNode() const
	{
		return RootNode;
	};
	UUAVGScriptRuntimeNodeRoot* SetupNewRuntimeScript();

	bool AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode);

	const UUAVGScriptRuntimeNodeRoot* GetConstRootNode() const
	{
		return RootNode;
	}

	UFUNCTION(BlueprintCallable)
	FText HelloScript();

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	class UEdGraph* MyEdGraph;
	
#endif
	UPROPERTY(BlueprintReadOnly)
	UUAVGScriptRuntimeNodeRoot* RootNode;

	//UPROPERTY(BlueprintReadOnly)
	//TArray<class UUAVGScriptRuntimeNode*> AllNodes;
};