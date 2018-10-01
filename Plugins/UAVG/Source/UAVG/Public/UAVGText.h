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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Character Display Delay (ms)", ShortTooltip = "ms"))
	uint8 CharacterDisplayDelayInMs = 200;
};
