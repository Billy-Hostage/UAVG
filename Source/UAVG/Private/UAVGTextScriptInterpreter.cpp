//NTRHostage

#include "UAVGTextScriptInterpreter.h"
#include "UAVGScriptText.h"

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
	case '^'://Comment
		SkipToNextLine(Response);
		break;

	case '@'://Trigger events with args
		SkipToNextLine(Response);//TODO
		break;

	case '!'://Add Env Descriptor
		SkipToNextLine(Response);//TODO
		break;
	case '%'://Remove Env Descriptor
		SkipToNextLine(Response);//TODO
		break;

	case '#'://Change Interpreter Behaviour
		SkipToNextLine(Response);//TODO
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
			SayBuffer.Add(FUAVGText(str.Left(str.Len() - 3), TextDisplayTime));
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
			SayBuffer.Add(FUAVGText(str, TextDisplayTime));
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

#undef SPLIT_LINE_STRING