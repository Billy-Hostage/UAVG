//NTRHostage

#include "UAVGText.h"

#include "UAVGWhiteboard.h"

FUAVGTextToken::FUAVGTextToken()
{
	Character = "";
	Type = EUAVGTextTokenType::TT_Normal;
}

FUAVGTextToken::FUAVGTextToken(FString Character, int32 TypewriterDelay)
{
	// This is actually possible with html markers implemented
	//check(Character.Len() == 1);
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
	return TextLine.IsEmpty();
}

int32 FUAVGText::GetTextLen()
{
	return GetTokenizedList().Num();
}

const TArray<FUAVGTextToken>& FUAVGText::GetTokenizedList(UUAVGWhiteboard* Whiteboard)
{
	if (CachedTokenList.Num() > 0 && LastUsedWhiteboard == Whiteboard) return CachedTokenList;
	return Tokenize(Whiteboard);
}

void FUAVGText::ClearTokenCache()
{
	CachedTokenList.Empty();
}

const TArray<FUAVGTextToken>& FUAVGText::Tokenize(UUAVGWhiteboard* Whiteboard)
{
	LastUsedWhiteboard = Whiteboard;
	const FString& LocalizedStringToTokenize = TextLine.ToString();
	const int32 StringLength = LocalizedStringToTokenize.Len();
	CachedTokenList.Empty();
	ApplyingRichMarkerStack.Empty();
	
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
				else if (ProcessedIndex + 1 >= StringLength || LocalizedStringToTokenize[ProcessedIndex + 1] == '<')
				{
					AddNormalCharacterToken('<');
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
			case '$':
				// prepare for a in-line(not at start of line) variable
				if (ProcessedIndex != 0 && Whiteboard)
				{
					FString VariableName = "";
					int32 ScannedCount = 1; // count-in '$'
					bool bFoundSpacing = false;
					for (; ProcessedIndex + ScannedCount < StringLength;)
					{
						if (LocalizedStringToTokenize[ProcessedIndex + ScannedCount] == ' ')
						{
							// found space, quitting
							bFoundSpacing = true;
							ScannedCount++;
							break;
						}

						VariableName.AppendChar(LocalizedStringToTokenize[ProcessedIndex + ScannedCount]);
						ScannedCount++;
					}

					if (bFoundSpacing)
					{
						const FString Out = Whiteboard->GetRawVariableConstRef(VariableName);
						for (const auto& Character : Out)
						{
							AddNormalCharacterToken(Character);
						}
						ProcessedIndex += ScannedCount;
					}
					else
					{
						// invalid
						AddNormalCharacterToken(CharToInspect);
						ProcessedIndex++;
						break;
					}
				}
				else
				{
					// we ignore this
					AddNormalCharacterToken(CharToInspect);
					ProcessedIndex++;
					break;
				}
				break;
			case '<':
				{
					FString RichMarkerName = "";
					int32 MarkerScannedCount = 1; // count-in '<'
					bool bFoundEndBracket = false;

					for (; ProcessedIndex + MarkerScannedCount < StringLength;)
					{
						if (LocalizedStringToTokenize[ProcessedIndex + MarkerScannedCount] == '>')
						{
							// found end bracket, stop scanning
							bFoundEndBracket = true;
							MarkerScannedCount++;
							break;
						}
						RichMarkerName.AppendChar(LocalizedStringToTokenize[ProcessedIndex + MarkerScannedCount]);
						MarkerScannedCount++;
					}

					if (!bFoundEndBracket)
					{
						// illegal marker. early break
						UE_LOG(LogTemp, Error, TEXT("Incomplete HTML Marker in %s at %d"), *LocalizedStringToTokenize, ProcessedIndex);
						AddNormalCharacterToken('<');
						ProcessedIndex++; // jump over '<', ignore MarkerScannedCount
						break;
					}

					if (RichMarkerName == "/")
					{
						// this is a end marker, pop a current stack
						ApplyingRichMarkerStack.Pop();
					}
					else
					{
						ApplyingRichMarkerStack.Push(RichMarkerName);
						
					}
					ProcessedIndex += MarkerScannedCount;
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
	FString FormationString = FString::Chr(Char);
	for (const auto& Marker : ApplyingRichMarkerStack)
	{
		FormationString = FString::Printf(TEXT("<%s>%s</>"), *Marker, *FormationString);
	}
	CachedTokenList.Add(FUAVGTextToken(FormationString, GetCharacterDisplayDelayInMs()));
}

void FUAVGText::AddBreakDelayToken(int32 TimeMs)
{
	CachedTokenList.Add(FUAVGTextToken(TimeMs));
}

void FUAVGText::AddLineBreakToken()
{
	CachedTokenList.Add(FUAVGTextToken(FString::Chr(NewLineCharacter), 0));
}
