//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.generated.h"

USTRUCT(BlueprintType, meta = (ToolTip = "UAVG Text"))
struct FUAVGText
{
	GENERATED_BODY()
public:
	FUAVGText()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Text Line"))
	FText TextLine;

	//TODO Make this better
	uint32 GetCharacterDisplayDelayInMs() const
	{
		if (TextLine.IsEmpty() || DisplayTimeInMs == 0) return 0;
		if (DisplayTimeInMs < 0) return CharacterDisplayDelayInMs;
		return DisplayTimeInMs / TextLine.ToString().Len();
	}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Character Display Delay (ms)", ShortTooltip = "ms", Tooltip = "Only Works when 'Display Delay' is Set to Negative"))
	int32 CharacterDisplayDelayInMs = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Display Delay (ms)", ShortTooltip = "ms", Tooltip = "Leave here Negative Number to Use 'Character Display Delay' "))
	int32 DisplayTimeInMs = 3000;
};
