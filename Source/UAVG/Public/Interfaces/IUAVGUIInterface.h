//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.h"
#include "UAVGComponent.h"
#include "IUAVGUIInterface.generated.h"

USTRUCT(BlueprintType)
struct FUAVGUILineInfo
{
	GENERATED_BODY()
public:
	FUAVGUILineInfo()
	{
	}
	FUAVGUILineInfo(TArray<FUAVGText> InText) : DesiredText(InText)
	{
	}

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "UAVG|Info"))
	TArray<FUAVGText> DesiredText;
};

UINTERFACE(Blueprintable)
class UUAVGUIInterface : public UInterface
{
	GENERATED_BODY()

};

class IUAVGUIInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnTextUpdated(int32 Index, const FText& NewText);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnNewLine(const FUAVGUILineInfo& Info);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnLineComplete();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnScriptComplete();

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void TriggerCustomEvent(const FString& EventName, const TArray<FString>& Arguments);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnEnvironmentDescriptorAdded(const FUAVGEnvironmentDescriptor& Added, const TArray<FUAVGEnvironmentDescriptor>& CurrentEnvironmentDescriptor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnEnvironmentDescriptorRemoved(const TArray<FUAVGEnvironmentDescriptor>& Removed, const TArray<FUAVGEnvironmentDescriptor>& CurrentEnvironmentDescriptor);
};