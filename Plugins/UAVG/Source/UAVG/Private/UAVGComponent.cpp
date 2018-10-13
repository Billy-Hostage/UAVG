//NTRHostage

#include "UAVGComponent.h"

#include "GameFramework/Actor.h"
#include "IUAVGActorInterface.h"
#include "IUAVGUIInterface.h"
#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"
#include "UAVGScriptRTNodeSaySingle.h"

void UUAVGComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_Speaking:
		Speak(DeltaTime);
		break;
	default:
		break;
	}
}

bool UUAVGComponent::InitializeNew(UObject* UIObject, AActor* ParentActor, bool bInstantNext/* = true*/)
{
	if (MyScript == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyScript cant be null!"));
		return false;
	}
	if (ParentActor == nullptr) ParentActor = GetOwner();

	if (UIObject && UIObject->GetClass()->ImplementsInterface(UUAVGUIInterface::StaticClass()))
	{
		UIInterface = UIObject;
	}
	if (ParentActor && ParentActor->GetClass()->ImplementsInterface(UUAVGActorInterface::StaticClass()))
	{
		ActorInterface = ParentActor;
	}
	this->CurrentNode = Cast<UUAVGScriptRuntimeNode>(MyScript->GetRuntimeRootNode());

	if (UIInterface == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UIInterface cant be null!"));
		return false;
	}
	if (ActorInterface == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ActorInterface cant be null!"));
		return false;
	}
	if (CurrentNode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Root Node Not Found in Script."));
		return false;
	}

	CurrentState = EUAVGRuntimeState::URS_ReadyForNext;

	if (bInstantNext)
	{
		Next();
	}

	return true;
}

FUAVGComponentNextResponse UUAVGComponent::Next()
{
	FUAVGComponentNextResponse Response;
	
	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_ReadyForNext:
		if (bCanNext)
		{
			NextNode(Response);
		}
		break;
	case EUAVGRuntimeState::URS_Speaking:
		TrySkip();
		break;
	case EUAVGRuntimeState::URS_Finished:
		UE_LOG(LogTemp, Error, TEXT("Script Already Finished!"));
		break;
	case EUAVGRuntimeState::URS_WaitingForAnswer:
		UE_LOG(LogTemp, Error, TEXT("Waiting for a Answer"));
		break;
	case EUAVGRuntimeState::URS_WaitingForCustomEvent:
		UE_LOG(LogTemp, Error, TEXT("Waiting for a Event"));
		break;
	case EUAVGRuntimeState::URS_NotInitialized:
		UE_LOG(LogTemp, Error, TEXT("UAVGComponent %s is not initialized!"), *GetName());
		break;
	case EUAVGRuntimeState::URS_MAX:
	case EUAVGRuntimeState::URS_NULL:
	default:
		UE_LOG(LogTemp, Error, TEXT("UAVGComponent %s Unexpected State"), *GetName());
		check(false);
		break;
	}

	Response.CurrentState = GetUAVGState();
	return Response;
}

void UUAVGComponent::EventHandled()
{
	if (GetUAVGState() != EUAVGRuntimeState::URS_WaitingForCustomEvent)
	{
		UE_LOG(LogTemp, Error, TEXT("We are not waiting for a Event!"));
		return;
	}

	FUAVGComponentNextResponse NextResponse;
	NextNode(NextResponse);
}

FText UUAVGComponent::BuildTextByIndex(const FUAVGText& InText, uint8 InNum)
{
	FString MyString = InText.TextLine.ToString();

	if (InNum > MyString.Len())
		return InText.TextLine;

	MyString = MyString.Left(InNum);
	return FText::FromString(MyString);
}

void UUAVGComponent::NextNode(FUAVGComponentNextResponse& OutResponse)
{
	LastNode = CurrentNode;
	CurrentNode = CurrentNode->GetNextNode();
	if (CurrentNode == nullptr)
	{
		OnScriptEnded();
		OutResponse.bSucceed = true;
		return;
	}

	FUAVGScriptRuntimeNodeArriveResponse ArriveResponse = CurrentNode->OnArrive();
	LastNodeResponse = ArriveResponse;//Cache it

	switch (ArriveResponse.NodeType)
	{
	case EUAVGRuntimeNodeType::URNT_Say:
		OnReachSayNode(OutResponse);
		break;
	case EUAVGRuntimeNodeType::URNT_CustomEvent:
		OnReachEventNode(OutResponse);
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Unexpected Node Type!"));
		OutResponse.bSucceed = false;
		break;
	}
}

void UUAVGComponent::TrySkip()
{
	if (!bCanPerformSkip) return;
	if(!ensure(GetUAVGState() == EUAVGRuntimeState::URS_Speaking)) return;

	SpeakDurationInMs += EachSkipTimeInMs;
}

void UUAVGComponent::Speak(float DeltaTime)
{
	check(DeltaTime > 0.f);
	if (DesiredText.Num() <= 0) return;

	SpeakDurationInMs += FMath::RoundHalfToEven(DeltaTime * 1000.f);

	for (int32 i = 0; i < DesiredText.Num(); ++i)
	{
		if (SpeakComplete[i]) continue;
		if (DisplayingNums[i] < 0) continue;
		int32 NewNums = SpeakDurationInMs / DesiredText[i].GetCharacterDisplayDelayInMs();
		if (NewNums >= DesiredText[i].TextLine.ToString().Len())
		{
			SpeakComplete[i] = true;
		}
		DisplayingNums[i] = NewNums;
		IUAVGActorInterface::Execute_OnTextUpdated(ActorInterface, i, BuildTextByIndex(DesiredText[i], NewNums));
		IUAVGUIInterface::Execute_OnTextUpdated(UIInterface, i, BuildTextByIndex(DesiredText[i], NewNums));
	}
	CheckIfLineCompleted();
}

void UUAVGComponent::CheckIfLineCompleted()
{
	for (bool b : SpeakComplete)
	{
		if (!b) return;
	}
	CurrentState = EUAVGRuntimeState::URS_ReadyForNext;
	IUAVGActorInterface::Execute_OnLineComplete(ActorInterface);
	IUAVGUIInterface::Execute_OnLineComplete(UIInterface);
}

void UUAVGComponent::OnScriptEnded()
{
	CurrentState = EUAVGRuntimeState::URS_Finished;
	IUAVGActorInterface::Execute_OnScriptComplete(ActorInterface);
	IUAVGUIInterface::Execute_OnScriptComplete(UIInterface);
}

void UUAVGComponent::OnReachSayNode(FUAVGComponentNextResponse& OutResponse)
{
	CurrentState = EUAVGRuntimeState::URS_Speaking;
	UpdateDesiredText(LastNodeResponse.DesiredTexts);
	OutResponse.bSucceed = true;
	IUAVGActorInterface::Execute_OnNewLine(ActorInterface, FUAVGActorLineInfo(DesiredText));
	IUAVGUIInterface::Execute_OnNewLine(UIInterface, FUAVGUILineInfo(DesiredText));
	SpeakDurationInMs = 0;//Reset timer
}

void UUAVGComponent::OnReachEventNode(FUAVGComponentNextResponse& OutResponse)
{
	CurrentState = EUAVGRuntimeState::URS_WaitingForCustomEvent;
	IUAVGActorInterface::Execute_TriggerCustomEvent(ActorInterface, LastNodeResponse.EventName, LastNodeResponse.EventArguments);
	IUAVGUIInterface::Execute_TriggerCustomEvent(UIInterface, LastNodeResponse.EventName, LastNodeResponse.EventArguments);
	OutResponse.bSucceed = true;
}

void UUAVGComponent::UpdateDesiredText(TArray<FUAVGText> NewText)
{
	DesiredText = NewText;

	DisplayingNums.Init(-1, DesiredText.Num());
	SpeakComplete.Init(false, DesiredText.Num());

	for (int32 i = 0; i < DesiredText.Num(); ++i)
	{
		if (!DesiredText[i].TextLine.IsEmpty())//Not Empty
		{
			DisplayingNums[i] = 0;
			if (DesiredText[i].GetCharacterDisplayDelayInMs() <= 0)
			{
			//Just Update Texts and Mark as Complete
			IUAVGActorInterface::Execute_OnTextUpdated(ActorInterface, i, DesiredText[i].TextLine);
			IUAVGUIInterface::Execute_OnTextUpdated(UIInterface, i, DesiredText[i].TextLine);
			SpeakComplete[i] = true;
			}
		}
		else//Empty Text is Always Completed
		{
			SpeakComplete[i] = true;
		}
	}
}
