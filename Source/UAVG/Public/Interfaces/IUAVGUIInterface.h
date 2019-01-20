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

USTRUCT(BlueprintType)
struct FUAVGUISelectionInfo
{
	GENERATED_BODY()
public:
	FUAVGUISelectionInfo()
	{
	}

	FUAVGUISelectionInfo(TArray<FText> InSelection) : SelectionTexts(InSelection)
	{
	}

	UPROPERTY(BlueprintReadOnly, meta = (DisplayName = "UAVG|Info"))
	TArray<FText> SelectionTexts;
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
	void OnFaceSelection(const FUAVGUISelectionInfo& Info);

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

	UFUNCTION(BlueprintImplementableEvent, Category = "Events")
	void OnEnvironmentDescriptorChanged(const FUAVGEnvironmentDescriptor& Old, const FUAVGEnvironmentDescriptor& New, const TArray<FUAVGEnvironmentDescriptor>& CurrentEnvironmentDescriptor);
};
