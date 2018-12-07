//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UAVGComponent.h"
#include "UAVGSaveGame.generated.h"

UCLASS(BlueprintType)
class UUAVGSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UUAVGSaveGame();

	UPROPERTY()
	class UUAVGScript* MyScript;

	UPROPERTY()
	class UUAVGScriptRuntimeNode* CurrentNode;

	UPROPERTY()
	class UUAVGScriptRuntimeNode* LastNode;

	UPROPERTY()
	TArray<FUAVGEnvironmentDescriptor> EnvironmentDescriptor;

	UPROPERTY()
	TArray<class UUAVGScript*> ScriptStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> CurrentNodeStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> LastNodeStack;
};
