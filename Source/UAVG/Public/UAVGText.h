//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.generated.h"

//The Text Struct used in UAVG Framework
USTRUCT(BlueprintType, meta = (ToolTip = "UAVG Text"))
struct FUAVGText
{
	GENERATED_BODY()
public:
	FUAVGText()
	{
	}

	FUAVGText(const FString& str, int32 DisplayTime = -1)
	{
		TextLine = FText::FromString(str);
		DisplayTimeInMs = DisplayTime;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Text Line"))
	FText TextLine;

	int32 GetCharacterDisplayDelayInMs() const
	{
		if (TextLine.IsEmpty() || DisplayTimeInMs == 0) return 0;
		if (DisplayTimeInMs < 0) return -1;//Needs Fallback
		return DisplayTimeInMs / GetTextLen();
	}

	//TODO We want to remove all html markers here
	int32 GetTextLen() const
	{
		return TextLine.ToString().Len();
	}
protected:
	//REMOVED
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Character Display Delay (ms)", ShortTooltip = "ms", Tooltip = "Only Works when 'Display Delay' is Set to Negative"))
	//int32 CharacterDisplayDelayInMs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Display Delay (ms)", ShortTooltip = "ms", Tooltip = "The time it takes to display all characters in text. \n Note that a empty text will be treated as DisplayTimeInMs == 0.f \n A negative number here will make runtime to find a fallback time"))
	int32 DisplayTimeInMs = 250;
};
