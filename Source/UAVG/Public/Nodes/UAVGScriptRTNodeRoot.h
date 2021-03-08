//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGScriptRTNode.h"
#include "UAVGScriptRTNodeRoot.generated.h"

UENUM(BlueprintType)
enum class EUAVGScriptCompleteBehaviour : uint8
{
	USCB_Nothing UMETA(DisplayName = "Nothing"),
	USCB_JumpToScriptReset UMETA(DisplayName = "Jump to Another Script with Reset"),
	//USCB_JumpToScriptNoReset UMETA(DisplayName = "Jump to Another Script without Reset"), TODO
	//USCB_TriggerEvent UMETA(DisplayName = "Trigger a Event"), TODO
};

//Every UAVGScript has this root node
UCLASS(Blueprintable)
class UAVG_API UUAVGScriptRuntimeNodeRoot : public UUAVGScriptRuntimeNode
{
	GENERATED_BODY()
public:
	UUAVGScriptRuntimeNodeRoot();

	virtual FUAVGScriptRuntimeNodeArriveResponse OnArrive(class UUAVGComponent* InComponent) override;

	///Properties Here

	UPROPERTY(BlueprintReadOnly)
	FName ScriptName;

	UPROPERTY(BlueprintReadOnly)
	int32 FallbackCharacterDisplayDelayInMs = 50;

	UPROPERTY(BlueprintReadOnly)
	EUAVGScriptCompleteBehaviour OnScriptCompleted = EUAVGScriptCompleteBehaviour::USCB_Nothing;

	UPROPERTY(BlueprintReadOnly)
	class UUAVGScript* ScriptToJump = nullptr;
};
