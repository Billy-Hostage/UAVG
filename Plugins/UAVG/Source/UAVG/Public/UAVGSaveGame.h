//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UAVGSaveGame.generated.h"

UCLASS(BlueprintType)
class UUAVGSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UUAVGSaveGame();

	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> CurrentNodes;

	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> LastNodes;
};
