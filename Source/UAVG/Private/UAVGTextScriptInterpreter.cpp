//NTRHostage

#include "UAVGTextScriptInterpreter.h"
#include "UAVGScriptText.h"
#include "UAVGSaveGame.h"

DEFINE_LOG_CATEGORY(LogUAVGRuntimeScriptTextInterpreter);
#define SPLIT_LINE_STRING "--------------"

UUAVGTextScriptInterpreter::UUAVGTextScriptInterpreter()
{

}

void UUAVGTextScriptInterpreter::SetupInterpreter(class UUAVGScriptText* InScriptTextAsset)
{
	if (!ensure(InScriptTextAsset))
		return;

	ScriptTextAsset = InScriptTextAsset;
	CachedScriptLines = InScriptTextAsset->GetLocalizedScriptLines();
	TextLinePointer = 0;
}

void UUAVGTextScriptInterpreter::WarpUAVGSaveGame(UUAVGSaveGame* InSave)
{
	InSave->UsingScriptTextAsset = ScriptTextAsset;
	InSave->LastTextLinePointer = LastCompleteLinePointer;
	InSave->TextDisplayTime = TextDisplayTimeLine;
}
void UUAVGTextScriptInterpreter::UnWarpUAVGSaveGame(UUAVGSaveGame* InSave)
{
	SetupInterpreter(InSave->UsingScriptTextAsset);
	TextLinePointer = InSave->LastTextLinePointer;
	TextDisplayTimeLine = InSave->TextDisplayTime;
}

void UUAVGTextScriptInterpreter::OnArrive(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	if (IsScriptTextCompleted())
	{
		//This should never happen!
		Response.NodeType = EUAVGRuntimeNodeType::URNT_MAX;
		return;
	}
	
	LastCompleteLinePointer = TextLinePointer;

	TCHAR CurrentLineCommand = TryFetchString()[0];
	switch (CurrentLineCommand)//Command Switch
	{
	case '@'://Trigger events with args
		ReachEventLine(Response);
		break;

	case '!'://Add Env Descriptor
		ReachAddEnvDescriptorLine(Response);
		break;
	case '%'://Remove Env Descriptor
		ReachRemoveEnvDescriptorLine(Response);
		break;

	case '#'://Change Interpreter Behaviour
		ReachInterpreterCommandLine(Response);
		break;

	///This might be done in ScriptText just once
	//case '$'://Find Key in StringTable and insert this line as speakline[0]
	//	//Force DisplayTime=0
	//	break;

	case '\''://Starts with a "'" ; Works the same as default
	default://say command as normal
		ReachSayLine(Response);
		break;
	}
}

bool UUAVGTextScriptInterpreter::IsScriptTextCompleted() const
{
	//Invalid means we have completed the script.
	return !CachedScriptLines.IsValidIndex(TextLinePointer);
}

void UUAVGTextScriptInterpreter::SkipToNextLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	TextLinePointer++;
	if (!IsScriptTextCompleted())
	{
		OnArrive(Response);
	}
	else
	{
		Response.NodeType = EUAVGRuntimeNodeType::URNT_NULL;
	}
}

FString UUAVGTextScriptInterpreter::TryFetchString(uint16 offset) const
{
	return CachedScriptLines[TextLinePointer + offset];
}

FString UUAVGTextScriptInterpreter::FetchString()
{
	return CachedScriptLines[TextLinePointer++];
}

void UUAVGTextScriptInterpreter::ReachEventLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	FString str = FetchString();
	TArray<FString> SplitedLine;
	FString EventName;
	TArray<FString> EventArgs;
	str.ParseIntoArray(SplitedLine, TEXT(" "));//Spacing-split
	for (int i = 0; i < SplitedLine.Num(); ++i)
	{
		FString token = SplitedLine[i];
		if (i == 0)
		{
			token = token.Right(token.Len() - 1);
			EventName = token;
			continue;
		}
		//i != 0
		EventArgs.Add(token);
	}

	Response.NodeType = EUAVGRuntimeNodeType::URNT_CustomEvent;
	Response.EventName = EventName;
	Response.EventArguments = EventArgs;
}

void UUAVGTextScriptInterpreter::ReachSayLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	TArray<FUAVGText> SayBuffer;
	bool FoundEndFlag = false;

	while (!IsScriptTextCompleted())
	{
		FString str = FetchString();

		if (str.StartsWith("'"))
		{
			str = str.Right(str.Len() - 1);
		}

		if (str.EndsWith("[pl]") || str.EndsWith("[lp]"))
		{
			//Force 0 timing since 'l'
			SayBuffer.Add(FUAVGText(str.Left(str.Len() - 4), 0));
			//break since 'p'
			FoundEndFlag = true;
			break;
		}
		else if (str.EndsWith("[p]"))
		{
			if (!bUseLineMode)
			{
				SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3), TextDisplayTimeCharacter));
			}
			else
			{
				SayBuffer[SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3)))].SetCharacterTimeFromLineTime(TextDisplayTimeLine);
			}
			//break since 'p'
			FoundEndFlag = true;
			break;
		}
		else if (str.EndsWith("[l]"))
		{
			//Force 0 timing since 'l'
			SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3), 0));
		}
		else
		{
			if (!bUseLineMode)
			{
				SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3), TextDisplayTimeCharacter));
			}
			else
			{
				SayBuffer[SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3)))].SetCharacterTimeFromLineTime(TextDisplayTimeLine);
			}
		}
	}

	if (!FoundEndFlag)
	{
		//No [p] found. Throw Fatal Error.
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Error, TEXT(SPLIT_LINE_STRING));
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Error, TEXT("Script Interpreter Error in Script %s"), *(ScriptTextAsset->GetName()));
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Error, TEXT("Expect a [p] as speak ending"));
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Error, TEXT("Last Processing Line %d"), LastCompleteLinePointer);
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Error, TEXT(SPLIT_LINE_STRING));
		Response.NodeType = EUAVGRuntimeNodeType::URNT_MAX;
	}
	else
	{
		//Good to go!
		Response.NodeType = EUAVGRuntimeNodeType::URNT_Say;
		Response.DesiredTexts = SayBuffer;
	}
}

void UUAVGTextScriptInterpreter::ReachAddEnvDescriptorLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	FString str = FetchString();
	TArray<FString> SplitedLine;
	FString EnvironmentToAdd;
	TArray<FString> AdditonalArgs;
	str.ParseIntoArray(SplitedLine, TEXT(" "));//Spacing-split

	for (int i = 0; i < SplitedLine.Num(); ++i)
	{
		FString token = SplitedLine[i];
		if (i == 0)
		{
			token = token.Right(token.Len() - 1);
			EnvironmentToAdd = token;
			continue;
		}

		AdditonalArgs.Add(token);
	}
	Response.NodeType = EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor;
	Response.EnvironmentToAdd = EnvironmentToAdd;
	Response.AdditonalEnvironmentArguments = AdditonalArgs;
}

void UUAVGTextScriptInterpreter::ReachRemoveEnvDescriptorLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	FString str = FetchString();
	TArray<FString> SplitedLine;
	str.ParseIntoArray(SplitedLine, TEXT(" "));//Spacing-split
	SplitedLine[0] = SplitedLine[0].Right(SplitedLine[0].Len() - 1);//Remove % mark

	Response.NodeType = EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor;
	Response.EnvironmentsToRemove = SplitedLine;
}

void UUAVGTextScriptInterpreter::ReachInterpreterCommandLine(FUAVGScriptRuntimeNodeArriveResponse& Response)
{
	FString str = TryFetchString();
	TArray<FString> SplitedLine;
	str.ParseIntoArray(SplitedLine, TEXT(" "));//Spacing-split
	FString Var = SplitedLine[0].Right(SplitedLine[0].Len() - 1);

	bool flagFoundVar = false;

	//@TODO Implement a command system
	
	if (Var == "display_time_line" && SplitedLine.IsValidIndex(1))
	{
		TextDisplayTimeLine = FCString::Atoi(*SplitedLine[1]);//Unsafe!
		flagFoundVar = true;
	}
	else if (Var == "display_time_character" && SplitedLine.IsValidIndex(1))
	{
		TextDisplayTimeCharacter = FCString::Atoi(*SplitedLine[1]);//Unsafe!
		flagFoundVar = true;
	}
	else if (Var == "display_mode" && SplitedLine.IsValidIndex(1))
	{
		if (SplitedLine[1] == "character")
		{
			bUseLineMode = false;
			flagFoundVar = true;
		}
		else if (SplitedLine[1] == "line")
		{
			bUseLineMode = true;
			flagFoundVar = true;
		}
	}

	if (!flagFoundVar)
	{
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Warning, TEXT(SPLIT_LINE_STRING));
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Warning, TEXT("Script Interpreter Error in Script %s"), *(ScriptTextAsset->GetName()));
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Warning, TEXT("Specified Variable %s not found."), *Var);
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Warning, TEXT("Last Processing Line %d"), LastCompleteLinePointer);
		UE_LOG(LogUAVGRuntimeScriptTextInterpreter, Warning, TEXT(SPLIT_LINE_STRING));
	}

	SkipToNextLine(Response);
}

#undef SPLIT_LINE_STRING