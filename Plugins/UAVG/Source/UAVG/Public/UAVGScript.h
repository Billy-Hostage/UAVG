//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "UAVGScript.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScript : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScript();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "General", meta = (DisplayName = "Script Name", ShortTooltip = "Name of Script", ToolTip = "The Name of This UAVG Script"))
	FName ScriptName;

	UPROPERTY(BlueprintReadOnly)
	class UUAVGScriptRuntimeNode* RootNode;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UUAVGScriptRuntimeNode*> AllNodes;

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	class UEdGraph* MyEdGraph;

#endif
};