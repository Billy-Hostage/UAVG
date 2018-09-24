//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "UAVGScript.generated.h"

class UUAVGScriptRuntimeNode;
class UUAVGScriptRuntimeNodeRoot;

UENUM(BlueprintType)
enum class EUAVGScriptStatus : uint8
{
	Preparing,
	ReadyForNext,
	Speaking,
	Questioning,//Currently useless
};

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGRuntimeScript, Log, All);

//Main Script Data Asset Holder for UAVG Plugin
UCLASS(Blueprintable, BlueprintType)
class UAVG_API UUAVGScript : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScript();

	virtual void TickUAVGScript(class AUAVGActor* Ticker);
	virtual void UAVGScriptNext(struct FUAVGActorNextResponse& InResponse);

	const UUAVGScriptRuntimeNodeRoot* GetConstRuntimeRootNode() const
	{
		return RootNode;
	};
	UUAVGScriptRuntimeNodeRoot* SetupNewRuntimeScript();

	bool AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode);

	UFUNCTION(BlueprintCallable)
	const FText& TestScript();

	virtual void ResetScriptProgress()
	{
		CurrentNode = Cast<UUAVGScriptRuntimeNode>(RootNode);
	}

	EUAVGScriptStatus GetScriptStatus()
	{
		return CurrentStatus;
	}

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	class UEdGraph* MyEdGraph;

#endif
protected:
	UPROPERTY(BlueprintReadOnly)
	UUAVGScriptRuntimeNodeRoot* RootNode;

	UPROPERTY(BlueprintReadOnly)
	UUAVGScriptRuntimeNode* CurrentNode;

	UPROPERTY(BlueprintReadOnly)
	TArray<class UUAVGScriptRuntimeNode*> AllNodes;
private:
	EUAVGScriptStatus CurrentStatus = EUAVGScriptStatus::Preparing;

	TArray<FString> StringToDisplay;
	TArray<FString> StringDisplaying;
};