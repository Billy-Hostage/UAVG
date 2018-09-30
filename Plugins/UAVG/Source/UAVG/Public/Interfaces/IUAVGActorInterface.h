//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.h"
#include "IUAVGActorInterface.generated.h"

USTRUCT(BlueprintType)
struct FUAVGActorLineInfo
{
	GENERATED_BODY()
public:
	FUAVGActorLineInfo()
	{
	}
	FUAVGActorLineInfo(TArray<FUAVGText> InText) : DesiredText(InText)
	{
	}

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "UAVG|Info"))
	TArray<FUAVGText> DesiredText;
};

UINTERFACE(Blueprintable)
class UUAVGActorInterface : public UInterface
{
	GENERATED_BODY()

};

class IUAVGActorInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnTextUpdated(int32 Index, const FText& NewText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnNewLine(const FUAVGActorLineInfo& Info);
};
