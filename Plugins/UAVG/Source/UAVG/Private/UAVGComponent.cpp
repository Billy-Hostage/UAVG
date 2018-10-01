//NTRHostage

#include "UAVGComponent.h"

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
		Next(FUAVGComponentNextCommand());
	}

	return true;
}

FUAVGComponentNextRespose UUAVGComponent::Next(FUAVGComponentNextCommand Command)
{
	FUAVGComponentNextRespose Response;
	
	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_Finished:
		UE_LOG(LogTemp, Error, TEXT("This Script is Already Finished!"));
		break;
	case EUAVGRuntimeState::URS_ReadyForNext:
		NextLine(Response);
		break;
	case EUAVGRuntimeState::URS_WaitingForAnswer:
		//TODO
		UE_LOG(LogTemp, Warning, TEXT("TODO : Implement Answer"));
		break;
	case EUAVGRuntimeState::URS_WaitingForCustomEvent:
		//TODO
		UE_LOG(LogTemp, Warning, TEXT("TODO : Implement CustomEvent"));
		break;
	case EUAVGRuntimeState::URS_Speaking:
		//TODO
		UE_LOG(LogTemp, Warning, TEXT("TODO : Implement Skip"));
		break;
	case EUAVGRuntimeState::URS_MAX:
	case EUAVGRuntimeState::URS_NULL:
	case EUAVGRuntimeState::URS_NotInitialized:
	default:
		UE_LOG(LogTemp, Error, TEXT("UAVGComponent %s is not initialized!"), *GetName());
		break;
	}

	Response.CurrentState = GetUAVGState();
	return Response;
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
			if (DesiredText[i].CharacterDisplayDelayInMs > 0)
			{
				
			}
			else
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

FText UUAVGComponent::BuildTextByIndex(const FUAVGText& InText, uint8 InNum)
{
	FString MyString = InText.TextLine.ToString();

	if (InNum > MyString.Len())
		return InText.TextLine;

	MyString = MyString.Left(InNum);
	return FText::FromString(MyString);
}

void UUAVGComponent::NextLine(FUAVGComponentNextRespose& OutResponse)
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
	if (ArriveResponse.bShouldUpdateDesiredTexts)
		UpdateDesiredText(ArriveResponse.DesiredTexts);
	OutResponse.bSucceed = true;
	IUAVGActorInterface::Execute_OnNewLine(ActorInterface, FUAVGActorLineInfo(DesiredText));
	IUAVGUIInterface::Execute_OnNewLine(UIInterface, FUAVGUILineInfo(DesiredText));
	CurrentState = EUAVGRuntimeState::URS_Speaking;
	SpeakDurationInMs = 0;//Reset timer
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
		int32 NewNums = SpeakDurationInMs / DesiredText[i].CharacterDisplayDelayInMs;
		if (NewNums >= DesiredText[i].TextLine.ToString().Len())
		{
			SpeakComplete[i] = true;
		}
		DisplayingNums[i] = NewNums;
		IUAVGActorInterface::Execute_OnTextUpdated(ActorInterface, i, BuildTextByIndex(DesiredText[i], NewNums));
		IUAVGUIInterface::Execute_OnTextUpdated(UIInterface, i, BuildTextByIndex(DesiredText[i], NewNums));
	}
	CheckIfSpeakCompleted();
}

void UUAVGComponent::CheckIfSpeakCompleted()
{
	for (bool b : SpeakComplete)
	{
		if (!b) return;
	}
	CurrentState = EUAVGRuntimeState::URS_ReadyForNext;
}

void UUAVGComponent::OnScriptEnded()
{
	/*OnFinished()*/
	CurrentState = EUAVGRuntimeState::URS_Finished;
}
