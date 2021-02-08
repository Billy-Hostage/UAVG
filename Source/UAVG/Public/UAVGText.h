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

	FUAVGText(const FString& str, int32 CharacterDisplayTime = -1)
	{
		TextLine = FText::FromString(str);
		CharacterDisplayTimeInMs = CharacterDisplayTime;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Text Line"))
	FText TextLine;

	int32 GetCharacterDisplayDelayInMs() const
	{
		return CharacterDisplayTimeInMs;
	}

	void SetCharacterTimeFromLineTime(int32 LineTime)
	{
		if (GetTextLen() <= 0) return;

		CharacterDisplayTimeInMs = static_cast<int32>(FMath::RoundHalfToZero(static_cast<float>(LineTime) / static_cast<float>(GetTextLen())));
	}
	
	//TODO We want to remove all html markers here
	int32 GetTextLen() const
	{
		return TextLine.ToString().Len();
	}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Character Display Time (ms)", ShortTooltip = "ms", Tooltip = "The time it takes to display all characters in text. \n Note that a empty text will be treated as DisplayTimeInMs == 0.f \n A negative number here will make runtime to use default value"))
	int32 CharacterDisplayTimeInMs = -1;
};
