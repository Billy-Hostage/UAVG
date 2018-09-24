//NTRHostge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAVGActor.generated.h"

UENUM(BlueprintType)
enum class EUAVGActorNextResponseType : uint8
{
	NON,
	Failed,
	Success,
	MAX
};

USTRUCT(BlueprintType)
struct FUAVGActorNextResponse
{
	GENERATED_BODY()
public:
	FUAVGActorNextResponse();

	UPROPERTY(BlueprintReadOnly)
	EUAVGActorNextResponseType Type = EUAVGActorNextResponseType::NON;
};

USTRUCT(BlueprintType)
struct FUAVGActorTickInfo
{
	GENERATED_BODY()
public:
	FUAVGActorTickInfo();

	UPROPERTY(BlueprintReadOnly, Category = "UAVG|Info", meta = (DisplayName = "Display String Array"))
	TArray<FString> DisplayStringArray;
};

UCLASS()
class UAVG_API AUAVGActor : public AActor
{
	GENERATED_BODY()
public:
	AUAVGActor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "UAVG|Operation")
	virtual FUAVGActorNextResponse Next();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UAVG", meta = (DisplayName = "Script"))
	class UUAVGScript* MyScript = nullptr;

	UFUNCTION(BlueprintImplementableEvent, Category = "UAVG|Event")
	void UAVGTick(const FUAVGActorTickInfo& InInfo);

	UFUNCTION(BlueprintCallable, Category = "Operation", meta = (ShortTooltip = "Reset Progress", ToolTip = "Reset Progress"))
	void ResetProgress();
};
