//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAVGText.h"
#include "UAVGScriptRTNode.h"//We want to use the structs in this header file
#include "UAVGComponent.generated.h"

UENUM(BlueprintType)
enum class EUAVGRuntimeState : uint8
{
	URS_NULL UMETA(Hidden),
	URS_NotInitialized UMETA(DisplayName = "Not Initialized"),
	URS_ReadyForNext UMETA(DisplayName = "Ready For Next"),
	URS_WaitingForAnswer UMETA(DisplayName = "Waiting For Answer"),
	URS_Speaking UMETA(DisplayName = "Speaking"),
	URS_WaitingForEvent UMETA(DisplayName = "Waiting For Event"),
	URS_Finished UMETA(DisplayName = "Finished"),
	URS_FatalError UMETA(DisplayName = "Fatal Error"),
	URS_MAX UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FUAVGComponentNextResponse
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "UAVG|Response")
	bool bSucceed = false;

	UPROPERTY(BlueprintReadOnly, Category = "UAVG|Response")
	EUAVGRuntimeState CurrentState = EUAVGRuntimeState::URS_NULL;
};

USTRUCT(BlueprintType)
struct FUAVGEnvironmentDescriptor
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
	FString Descriptor;

	UPROPERTY(BlueprintReadOnly)
	TArray<FString> AdditonalArguments;
};

/*
 * This is the basic Runtime Component for UAVG Plugin
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class UAVG_API UUAVGComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UUAVGComponent()
	{
		PrimaryComponentTick.bCanEverTick = true;
	}

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "UAVG")
	bool InitializeNew(UObject* UIObject, AActor* ParentActor, bool bInstantNext = true);

	UFUNCTION(BlueprintCallable, Category = "UAVG|Save")
	bool InitializeFromSave(UObject* UIObject, AActor* ParentActor, class UUAVGSaveGame* SaveData);

	/*UFUNCTION(BlueprintCallable, Category = "UAVG")
	void Reset();*/

	UFUNCTION(BlueprintCallable, Category = "UAVG|Save")
	class UUAVGSaveGame* Save(class UUAVGSaveGame* SaveObj);

	//This should be called when user is trying to do "Next" Operation
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	FUAVGComponentNextResponse Next();

	//This should be called when a custom event is handled by user
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	void EventHandled();
protected:
	UObject* UIInterface = nullptr;
	AActor* ActorInterface = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UAVG|Config")
	class UUAVGScript* MyScript = nullptr;
public:
	///Getters
	UFUNCTION(BlueprintPure, Category = "UAVG|State")
	EUAVGRuntimeState GetUAVGState() const
	{
		return CurrentState;
	}
private:
	EUAVGRuntimeState CurrentState = EUAVGRuntimeState::URS_NotInitialized;

	int32 SpeakDurationInMs = 0;

	class UUAVGScriptRuntimeNode* LastNode = nullptr;
	class UUAVGScriptRuntimeNode* CurrentNode = nullptr;

	///These arrays are aligned.
	TArray<bool> SpeakComplete;
	TArray<int32> DisplayingNums;
	TArray<FUAVGText> DesiredText;

	TArray<FUAVGEnvironmentDescriptor> EnvironmentDescriptor;

	FUAVGScriptRuntimeNodeArriveResponse LastNodeResponse;

	void OnReachSayNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachEventNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachEnvironmentDescriptorNode(FUAVGComponentNextResponse& OutResponse);

	void UpdateDesiredText(TArray<FUAVGText> NewText);
	void UpdateDisplayNum(int32 Index);

	FText BuildTextByIndex(const FUAVGText& InText, uint8 InNum);

	void CheckIfLineCompleted();
protected:
	void NextNode(FUAVGComponentNextResponse& OutResponse);
	void ProcessNode(FUAVGComponentNextResponse& OutResponse);

	void TrySkip();

	void Speak(float DeltaTime);

	void OnScriptEnded();

	void WarpSaveObject(class UUAVGSaveGame* InSave);
	void UnWarpSaveObject(class UUAVGSaveGame* InSave);
	void UnWarpEnvironmentDescriptor(TArray<FUAVGEnvironmentDescriptor> SavedDescriptor);

	///Configs Here

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config")
	bool bCanNext = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config|Skipping")
	bool bCanPerformSkip = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config|Skipping")
	int32 EachSkipTimeInMs = 200;
};
