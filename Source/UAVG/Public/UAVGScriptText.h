//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptText.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UAVG_API UUAVGScriptText : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScriptText();

protected:
	UPROPERTY()
	TArray<FString> ScriptLines;

#ifdef WITH_EDITOR
public:
	void EditorSetupScriptText(const FString& ScriptString);
#endif
};
