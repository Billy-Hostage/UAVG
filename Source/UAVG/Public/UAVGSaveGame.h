//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UAVGComponent.h"
#include "Nodes/UAVGScriptRTNode.h"
#include "UAVGSaveGame.generated.h"

UCLASS(BlueprintType)
class UUAVGSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UUAVGSaveGame();

	///General
	UPROPERTY()
	class UUAVGScript* MyScript;

	UPROPERTY()
	EUAVGRuntimeState RTState;

	UPROPERTY()
	class UUAVGScriptRuntimeNode* CurrentNode;

	UPROPERTY()
	class UUAVGScriptRuntimeNode* LastNode;

	//You might wish to revive scenes from savedata using this variable
	UPROPERTY(BlueprintReadOnly)
	TArray<FUAVGEnvironmentDescriptor> EnvironmentDescriptor;

	UPROPERTY()
	TArray<class UUAVGScript*> ScriptStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> CurrentNodeStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> LastNodeStack;

	//You might wish to use this in save management
	UPROPERTY(BlueprintReadOnly)
	TArray<FUAVGText> RecentDisplayingText;

	///Node Specific

	UPROPERTY()
	class UUAVGScriptText* UsingScriptTextAsset;
	UPROPERTY()
	uint32 LastTextLinePointer = 0;
	UPROPERTY()
	int32 TextDisplayTime = 250;
};
