//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UAVGText.h"
#include "UAVGComponent.generated.h"

UENUM(BlueprintType)
enum class EUAVGRuntimeState : uint8
{
	URS_NULL,
	URS_NotInitialized,
	URS_ReadyForNext,
	URS_WaitingForAnswer,
	URS_Speaking,
	URS_WaitingForCustomEvent,
	URS_Finished,
	URS_MAX
};

UENUM(BlueprintType)
enum class EUAVGComponentNextCommandType : uint8
{
	UNC_NULL,
	UNC_SimpleNextLine,
	UNC_Answer,
	UNC_CustomEventCompleted,
	UNC_MAX
};

USTRUCT(BlueprintType)
struct FUAVGComponentNextRespose
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "UAVG|Response")
	bool bSucceed = false;

	UPROPERTY(BlueprintReadOnly, Category = "UAVG|Response")
	EUAVGRuntimeState CurrentState = EUAVGRuntimeState::URS_NULL;
};

USTRUCT(BlueprintType)
struct FUAVGComponentNextCommand
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EUAVGComponentNextCommandType CommandType = EUAVGComponentNextCommandType::UNC_SimpleNextLine;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class UAVG_API UUAVGComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UUAVGComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "UAVG")
	bool InitializeNew(UObject* UIObject, AActor* ParentActor, bool bInstantNext = true);

	/*UFUNCTION(BlueprintCallable, Category = "UAVG|Save")*/
	/*bool InitializeFromSave(class UUAVGSave* SaveData);*/

	/*UFUNCTION(BlueprintCallable, Category = "UAVG|Save")*/
	/*UUAVGSave* Save()*/

	UFUNCTION(BlueprintCallable, Category = "UAVG|Command")
	FUAVGComponentNextRespose Next(FUAVGComponentNextCommand Command);
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

	class UUAVGScriptRuntimeNode* LastNode = nullptr;
	class UUAVGScriptRuntimeNode* CurrentNode = nullptr;

	TArray<FUAVGText> DesiredText;
protected:
	void NextLine(FUAVGComponentNextRespose& OutResponse);

	void Speak();
};
