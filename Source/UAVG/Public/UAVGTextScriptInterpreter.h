//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"//Use struct FUAVGScriptRuntimeNodeArriveResponse
#include "UAVGTextScriptInterpreter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGRuntimeScriptTextInterpreter, Log, All);

/*
 *TODO This class needs refactor
 */
UCLASS()
class UUAVGTextScriptInterpreter : public UObject
{
	GENERATED_BODY()
public:
	UUAVGTextScriptInterpreter();

	void SetupInterpreter(class UUAVGScriptText* InScriptTextAsset);

	void OnArrive(FUAVGScriptRuntimeNodeArriveResponse& Response);

	bool IsScriptTextCompleted() const;
protected:
	UPROPERTY()
	class UUAVGScriptText* ScriptTextAsset = nullptr;

	UPROPERTY()
	TArray<FString> CachedScriptLines;

	UPROPERTY()
	uint32 TextLinePointer = 0;
	UPROPERTY()
	uint32 LastCompleteLinePointer = 0;

	///Below are interpreter properties
	UPROPERTY()
	int32 TextDisplayTime = 250;
private:

	void SkipToNextLine(FUAVGScriptRuntimeNodeArriveResponse& Response);

	///These Funcs are not safe.
	//Does not change pointer count.
	FString TryFetchString(uint16 offset = 0) const;
	//Increase Pointer by one
	FString FetchString();
protected:

	///Below are interpreter funcs.
	virtual void ReachSayLine(FUAVGScriptRuntimeNodeArriveResponse& Response);

	virtual void ReachEventLine(FUAVGScriptRuntimeNodeArriveResponse& Response);
	
	virtual void ReachAddEnvDescriptor(FUAVGScriptRuntimeNodeArriveResponse& Response);
	virtual void ReachRemoveEnvDescriptor(FUAVGScriptRuntimeNodeArriveResponse& Response);
};