//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAVGText.h"
#include "Nodes/UAVGScriptRTNode.h"//We want to use the structs in this header file
#include "UAVGComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGRuntimeComponent, Log, All);

UENUM(BlueprintType)
enum class EUAVGRuntimeState : uint8
{
	URS_NULL UMETA(Hidden),
	URS_NotInitialized UMETA(DisplayName = "Not Initialized"),
	URS_ReadyForNext UMETA(DisplayName = "Ready For Next"),
	URS_Speaking UMETA(DisplayName = "Speaking"),
	URS_WaitingForEvent UMETA(DisplayName = "Waiting For Event"),
	URS_WaitingForSelection UMETA(DisplayName = "Waiting For Selection"),
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

	UFUNCTION(BlueprintCallable, Category = "UAVG")
	void Reset();

	UFUNCTION(BlueprintCallable, Category = "UAVG|Save")
	class UUAVGSaveGame* Save(class UUAVGSaveGame* SaveObj);

	//This should be called when user is trying to do "Next" Operation
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	FUAVGComponentNextResponse Next();

	//This should be called when a custom event is handled by user
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	void EventHandled();

	//Select a Route for Selection Node (Pass a Negative Index to use the default selection for that node)
	//Note that you still need to Manually Call Next() for the next node.
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	void SetSelection(int32 InIndex);

	//Change a Script(When not Initialized)
	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	void ChangeScript(UUAVGScript* NewScript);

	//Check if we can do next without triggering warnings and errors
	UFUNCTION(BlueprintPure, Category = "UAVG")
	bool CanNext() const;

	UFUNCTION(BlueprintPure, Category = "UAVG")
	class UUAVGScript* GetCurrentScript() const;

	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	void SetWhiteboardObject(class UUAVGWhiteboard* Object);

	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	class UUAVGWhiteboard* GetWhiteboardObject(bool bCreateIfNull = false);
protected:
	UPROPERTY()
	UObject* UIInterface = nullptr;
	UPROPERTY()
	AActor* ActorInterface = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "UAVG|Config")
	class UUAVGScript* MyScript = nullptr;
	
	///These Arrays are aligned
	UPROPERTY()
	TArray<class UUAVGScript*> ScriptStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> CurrentNodeStack;
	UPROPERTY()
	TArray<class UUAVGScriptRuntimeNode*> LastNodeStack;
public:
	///Getters
	UFUNCTION(BlueprintPure, Category = "UAVG|State")
	EUAVGRuntimeState GetUAVGState() const
	{
		return CurrentState;
	}
private:
	void GenerateEmptyWhiteboard();
	
	EUAVGRuntimeState CurrentState = EUAVGRuntimeState::URS_NotInitialized;

	int32 SpeakDurationInMs = 0;

	UPROPERTY()
	class UUAVGScriptRuntimeNode* LastNode = nullptr;
	UPROPERTY()
	class UUAVGScriptRuntimeNode* CurrentNode = nullptr;

	UPROPERTY()
	class UUAVGWhiteboard* WhiteboardObject = nullptr;

	///These arrays are aligned.
	TArray<bool> SpeakComplete;
	TArray<int32> DisplayingNums;
	TArray<FUAVGText> DesiredText;

	TArray<FUAVGEnvironmentDescriptor> EnvironmentDescriptor;

	TArray<FUAVGText> RecentDisplayingText;
	FUAVGScriptRuntimeNodeArriveResponse LastNodeResponse;

	void OnReachSayNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachEventNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachEnvironmentDescriptorNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachRunSubScriptNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachSelectionNode(FUAVGComponentNextResponse& OutResponse);
	void OnReachSetWhiteboardVariableNode(FUAVGComponentNextResponse& OutResponse);

	void UpdateDesiredText(TArray<FUAVGText> NewText);

	FText BuildTextByNum(FUAVGText& InText, uint8 InNum);

	void CheckIfLineCompleted();

	void ChangeEnvironmentDescriptor(int32 IndexToChange);
protected:
	void NextNode(FUAVGComponentNextResponse& OutResponse);
	void ProcessNode(FUAVGComponentNextResponse& OutResponse);

	//Try to skip.
	void TrySkip();

	void Speak(float DeltaTime);

	void CompleteScript();

	void OnScriptEnded();

	void WarpSaveObject(class UUAVGSaveGame* InSave);
	void UnWarpSaveObject(class UUAVGSaveGame* InSave);
	void UnWarpEnvironmentDescriptor(TArray<FUAVGEnvironmentDescriptor> SavedDescriptor);

	///Configs Here

	//Set it to false to manually disable Next() command
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config")
	bool bCanNext = true;

	//Save Whiteboard Data in built-in save objects or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config")
	bool bHandlesWhiteboardSave = false;

	//Set it to false to disable skip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config|Skipping")
	bool bCanPerformSkip = true;

	//Determines skipping speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAVG|Config|Skipping")
	int32 EachSkipTimeInMs = 200;
};
