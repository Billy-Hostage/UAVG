//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.h"
#include "UAVGScriptRTNode.generated.h"

UENUM(BlueprintType)
enum class EUAVGRuntimeNodeType : uint8
{
	URNT_NULL,
	URNT_Root,
	URNT_Say,
	URNT_CustomEvent,
	URNT_EnvironmentDescriptor,
	URNT_MAX,
};

struct FUAVGScriptRuntimeNodeArriveResponse
{
public:
	FUAVGScriptRuntimeNodeArriveResponse()
	{
	}
	FUAVGScriptRuntimeNodeArriveResponse(EUAVGRuntimeNodeType Type)
	{
		NodeType = Type;
	}

	EUAVGRuntimeNodeType NodeType = EUAVGRuntimeNodeType::URNT_NULL;

	TArray<FUAVGText> DesiredTexts;

	FString EventName;
	TArray<FString> EventArguments;

	FString EnvironmentToAdd;
	TArray<FString> AdditonalEnvironmentArguments;
	
	TArray<FString> EnvironmentToRemove;
};

UCLASS(Abstract, BlueprintType)
class UAVG_API UUAVGScriptRuntimeNode : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNode();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive()
	{
		return FUAVGScriptRuntimeNodeArriveResponse();
	}
	virtual UUAVGScriptRuntimeNode* GetNextNode();

	virtual void WarpUAVGSaveGame(class UUAVGSaveGame* InSave){}
	virtual void UnWarpUAVGSaveGame(class UUAVGSaveGame* InSave){}

	/*Called When Editor Saving Graph*/
	virtual bool SetChild(TArray<UUAVGScriptRuntimeNode*> InChildNodes);
	virtual bool SetParent(TArray<UUAVGScriptRuntimeNode*> InParentNodes);
	bool CheckNodeCanBePaentOrChild(UUAVGScriptRuntimeNode* InNode) const;
	/*End Called When Editor Saving Graph*/
public:
	UPROPERTY()
		TArray<UUAVGScriptRuntimeNode*> MyParentNodes;
	UPROPERTY()
		TArray<UUAVGScriptRuntimeNode*> MyChildNodes;
};