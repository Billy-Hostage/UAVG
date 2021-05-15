//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UAVGText.generated.h"

class UUAVGWhiteboard;

enum class EUAVGTextTokenType
{
	TT_Nul,
	TT_Normal,
	TT_Delay,    // Timed Break
};

/*
* This is intended for internal usage only
* shall not exposed to blueprint
*/
USTRUCT()
struct FUAVGTextToken
{
	GENERATED_BODY()
	
	FUAVGTextToken();
	FUAVGTextToken(FString Character, int32 TypewriterDelay);
	FUAVGTextToken(int32 Break);
	
	FString Character;
	
	int32 TypewriterDelay;

	EUAVGTextTokenType Type = EUAVGTextTokenType::TT_Nul;
};

//The Text Struct used in UAVG Framework
USTRUCT(BlueprintType, meta = (ToolTip = "UAVG Text"))
struct FUAVGText
{
	GENERATED_BODY()
public:
	FUAVGText();

	FUAVGText(const FString& str, int32 CharacterDisplayTime = -1, int32 BreakDelayTime = 500);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Text Line"))
	FText TextLine;

	int32 GetCharacterDisplayDelayInMs() const
	{
		return CharacterDisplayTimeInMs;
	}
	void SetCharacterDisplayDelayInMs(int time)
	{
		CharacterDisplayTimeInMs = time;
		CachedTokenList.Empty();
	}

	void SetCharacterTimeFromLineTime(int32 LineTime);

	bool IsEmpty();
	
	int32 GetTextLen();

	const TArray<FUAVGTextToken>& GetTokenizedList(UUAVGWhiteboard* Whiteboard = nullptr);

	void ClearTokenCache();
protected:
	const TArray<FUAVGTextToken>& Tokenize(UUAVGWhiteboard* Whiteboard = nullptr);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (DisplayName = "Character Display Time (ms)", ShortTooltip = "ms", Tooltip = "The time it takes to display a character in text. \n A negative number here will make runtime to use default value"))
	int32 CharacterDisplayTimeInMs = -1;
	
	int32 BreakDelayTimeInMs = 500;
private:
	void AddNormalCharacterToken(TCHAR Char);

	void AddBreakDelayToken(int32 TimeMs);

	void AddLineBreakToken();
	
	UPROPERTY(Transient)
	TArray<FUAVGTextToken> CachedTokenList;

	static const TCHAR NewLineCharacter;

	UUAVGWhiteboard* LastUsedWhiteboard = nullptr;
};
