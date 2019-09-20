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

	TArray<FString> GetLocalizedScriptLines();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> ScriptLines;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class UStringTable*> StringTableToSearch;

#ifdef WITH_EDITOR
public:
	void EditorSetupScriptText(const FString& ScriptString);
#endif
};
