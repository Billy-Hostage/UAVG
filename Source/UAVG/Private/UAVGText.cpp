//NTRHostage

#include "UAVGText.h"

FUAVGTextToken::FUAVGTextToken()
{
	Character = "";
	Type = EUAVGTextTokenType::TT_Normal;
}

FUAVGTextToken::FUAVGTextToken(FString Character, int32 TypewriterDelay)
{
	check(Character.Len() == 1);
	this->Character = Character;
	this->TypewriterDelay = TypewriterDelay;
	Type = EUAVGTextTokenType::TT_Normal;
}

FUAVGTextToken::FUAVGTextToken(int32 Break)
{
	check(Break >= 0);
	TypewriterDelay = Break;
	Type = EUAVGTextTokenType::TT_Delay;
}

const TCHAR FUAVGText::NewLineCharacter = '\n';

FUAVGText::FUAVGText()
{
}

FUAVGText::FUAVGText(const FString& str, int32 CharacterDisplayTime, int32 BreakDelayTime)
{
	TextLine = FText::FromString(str);
	CharacterDisplayTimeInMs = CharacterDisplayTime;
	BreakDelayTimeInMs = BreakDelayTime;
}

void FUAVGText::SetCharacterTimeFromLineTime(int32 LineTime)
{
	if (GetTextLen() <= 0) return;

	CharacterDisplayTimeInMs = static_cast<int32>(FMath::RoundHalfToZero(static_cast<float>(LineTime) / static_cast<float>(GetTextLen())));
}

bool FUAVGText::IsEmpty()
{
	return GetTextLen() == 0;
}

int32 FUAVGText::GetTextLen()
{
	return GetTokenizedList().Num();
}

const TArray<FUAVGTextToken>& FUAVGText::GetTokenizedList()
{
	if (CachedTokenList.Num() > 0) return CachedTokenList;
	return Tokenize();
}

void FUAVGText::ClearTokenCache()
{
	CachedTokenList.Empty();
}

const TArray<FUAVGTextToken>& FUAVGText::Tokenize()
{
	const FString& LocalizedStringToTokenize = TextLine.ToString();
	const int32 StringLength = LocalizedStringToTokenize.Len();
	CachedTokenList.Empty();
	
	int32 ProcessedIndex = 0;
	while (ProcessedIndex < StringLength)
	{
		const TCHAR& CharToInspect = LocalizedStringToTokenize[ProcessedIndex];
		switch (CharToInspect)
		{
			case '\\':
				if (ProcessedIndex + 1 >= StringLength || LocalizedStringToTokenize[ProcessedIndex + 1] == '\\')
				{
					AddNormalCharacterToken('\\');
					ProcessedIndex += 2;
				}
				else if (LocalizedStringToTokenize[ProcessedIndex + 1] == 'b')
				{
					AddBreakDelayToken(BreakDelayTimeInMs);
					ProcessedIndex += 2;
				}
				else if (LocalizedStringToTokenize[ProcessedIndex + 1] == 'n')
				{
					AddLineBreakToken();
					ProcessedIndex += 2;
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Unimplememnted Symble in %s"), *LocalizedStringToTokenize);
					ProcessedIndex += 2;
				}
				break;
			default:
				AddNormalCharacterToken(CharToInspect);
				ProcessedIndex++;
				break;
		}
	}
	
	return CachedTokenList;
}

void FUAVGText::AddNormalCharacterToken(TCHAR Char)
{
	//@TODO maybe filter out punctuations
	CachedTokenList.Add(FUAVGTextToken(FString::Chr(Char), GetCharacterDisplayDelayInMs()));
}

void FUAVGText::AddBreakDelayToken(int32 TimeMs)
{
	CachedTokenList.Add(FUAVGTextToken(TimeMs));
}

void FUAVGText::AddLineBreakToken()
{
	CachedTokenList.Add(FUAVGTextToken(FString::Chr(NewLineCharacter), 0));
}
