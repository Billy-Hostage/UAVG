//NTRHostage

#include "UAVGComponent.h"

#include "GameFramework/Actor.h"
#include "IUAVGActorInterface.h"
#include "IUAVGUIInterface.h"
#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"
#include "UAVGScriptRTNodeSaySingle.h"
#include "UAVGSaveGame.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogUAVGRuntimeComponent);

void UUAVGComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_Speaking:
		Speak(DeltaTime);
		break;
	}
}

bool UUAVGComponent::InitializeNew(UObject* UIObject, AActor* ParentActor, bool bInstantNext/* = true*/)
{
	if (GetUAVGState() != EUAVGRuntimeState::URS_NotInitialized)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Component %s has been initialized already."), *GetName());
		return false;
	}

	if (MyScript == nullptr)
	{
		UE_LOG(LogUAVGRuntimeComponent, Warning, TEXT("MyScript cant be null!"));
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
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("UIInterface cant be null!"));
		return false;
	}
	if (ActorInterface == nullptr)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("ActorInterface cant be null!"));
		return false;
	}
	if (CurrentNode == nullptr)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Root Node Not Found in Script."));
		return false;
	}

	CurrentState = EUAVGRuntimeState::URS_ReadyForNext;

	if (bInstantNext)
	{
		Next();
	}

	return true;
}

bool UUAVGComponent::InitializeFromSave(UObject* UIObject, AActor* ParentActor, class UUAVGSaveGame* SaveData)
{
	if (GetUAVGState() != EUAVGRuntimeState::URS_NotInitialized)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Component %s has been initialized already."), *GetName());
		return false;
	}

	if (!SaveData)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Invalid SaveData"));
		return false;
	}
	if (SaveData->MyScript != MyScript)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Incompatible SaveData"));
		return false;
	}

	if (MyScript == nullptr)
	{
		UE_LOG(LogUAVGRuntimeComponent, Warning, TEXT("MyScript cant be null!"));
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

	UnWarpSaveObject(SaveData);
	if (CurrentNode)
	{
		CurrentNode->UnWarpUAVGSaveGame(SaveData);
		FUAVGComponentNextResponse Response;
		ProcessNode(Response);
		return true;
	}

	return false;
}

void UUAVGComponent::Reset()
{
	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_NotInitialized:
	case EUAVGRuntimeState::URS_NULL:
	case EUAVGRuntimeState::URS_MAX:
		UE_LOG(LogUAVGRuntimeComponent, Warning, TEXT("UAVGComponent %s no need to reset"), *GetName());
		return;//Stop here
	}

	CurrentNode = nullptr;
	LastNode = nullptr;
	UIInterface = nullptr;
	ActorInterface = nullptr;
	SpeakDurationInMs = 0;
	SpeakComplete.Empty();
	DisplayingNums.Empty();
	DesiredText.Empty();
	ScriptStack.Empty();
	CurrentNodeStack.Empty();
	LastNodeStack.Empty();
	CurrentState = EUAVGRuntimeState::URS_NotInitialized;
}

UUAVGSaveGame* UUAVGComponent::Save(UUAVGSaveGame* SaveObj/* = nullptr*/)
{
	if (GetUAVGState() == EUAVGRuntimeState::URS_NotInitialized)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Component %s hasn't been initialized yet."), *GetName());
		return nullptr;
	}
	else if (GetUAVGState() == EUAVGRuntimeState::URS_FatalError)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Fatal Error in UAVGComponent %s"), *GetName());
		return nullptr;
	}
	else if (GetUAVGState() == EUAVGRuntimeState::URS_Finished)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("UAVGComponent %s has finished"), *GetName());
		return nullptr;
	}

	if (!SaveObj)
	{
		SaveObj = CastChecked<UUAVGSaveGame>
			(UGameplayStatics::CreateSaveGameObject(UUAVGSaveGame::StaticClass()));
	}

	if(!ensure(SaveObj)) return nullptr;

	WarpSaveObject(SaveObj);
	if (CurrentNode)
		CurrentNode->WarpUAVGSaveGame(SaveObj);

	return SaveObj;
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
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Script Already Finished!"));
		break;
	case EUAVGRuntimeState::URS_WaitingForAnswer:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Waiting for a Answer"));
		break;
	case EUAVGRuntimeState::URS_WaitingForEvent:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Waiting for a Event"));
		break;
	case EUAVGRuntimeState::URS_NotInitialized:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("UAVGComponent %s is not initialized!"), *GetName());
		break;
	case EUAVGRuntimeState::URS_FatalError:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Fatal Error in UAVGComponent %s"), *GetName());
		break;
	case EUAVGRuntimeState::URS_MAX:
	case EUAVGRuntimeState::URS_NULL:
	default:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("UAVGComponent %s Unexpected State"), *GetName());
		CurrentState = EUAVGRuntimeState::URS_FatalError;
		break;
	}

	Response.CurrentState = GetUAVGState();
	return Response;
}

void UUAVGComponent::EventHandled()
{
	if (GetUAVGState() != EUAVGRuntimeState::URS_WaitingForEvent)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("We are not waiting for a Event!"));
		return;
	}
	
	FUAVGComponentNextResponse NextResponse;
	NextNode(NextResponse);
}

void UUAVGComponent::ChangeScript(UUAVGScript* NewScript)
{
	if (NewScript && NewScript->IsValidLowLevel())
	{
		if (GetUAVGState() == EUAVGRuntimeState::URS_Finished)
		{
			Reset();
			MyScript = NewScript;
		}
		else if (GetUAVGState() == EUAVGRuntimeState::URS_NotInitialized)
		{
			MyScript = NewScript;
		}
		else
		{
			UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("UAVGComponent %s cant swap script"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Script invalid"));
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

void UUAVGComponent::NextNode(FUAVGComponentNextResponse& OutResponse)
{
	LastNode = CurrentNode;
	CurrentNode = CurrentNode->GetNextNode();
	if (CurrentNode == nullptr)
	{
		if(ScriptStack.Num() == 0)
		{
			OnScriptEnded();
			OutResponse.bSucceed = true;
			return;
		}
		else
		{
			MyScript = ScriptStack.Pop(true);
			CurrentNode = CurrentNodeStack.Pop(true);
			LastNode = LastNodeStack.Pop(true);
			NextNode(OutResponse);
			return;
		}
	}

	ProcessNode(OutResponse);
}

void UUAVGComponent::ProcessNode(FUAVGComponentNextResponse& OutResponse)
{
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
	case EUAVGRuntimeNodeType::URNT_EnvironmentDescriptor:
		OnReachEnvironmentDescriptorNode(OutResponse);
		break;
	case EUAVGRuntimeNodeType::URNT_RunSubScript:
		OnReachRunSubScriptNode(OutResponse);
		break;
	default:
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("Unexpected Node Type!"));
		CurrentState = EUAVGRuntimeState::URS_FatalError;
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
	CurrentState = EUAVGRuntimeState::URS_WaitingForEvent;
	IUAVGActorInterface::Execute_TriggerCustomEvent(ActorInterface, LastNodeResponse.EventName, LastNodeResponse.EventArguments);
	IUAVGUIInterface::Execute_TriggerCustomEvent(UIInterface, LastNodeResponse.EventName, LastNodeResponse.EventArguments);
	OutResponse.bSucceed = true;
}

void UUAVGComponent::OnReachEnvironmentDescriptorNode(FUAVGComponentNextResponse& OutResponse)
{
	if (!LastNodeResponse.EnvironmentToAdd.IsEmpty())
	{
		bool flagIsChange = false;

		for (int32 i = 0; i < EnvironmentDescriptor.Num(); ++i)
		{
			if (EnvironmentDescriptor[i].Descriptor == LastNodeResponse.EnvironmentToAdd)
			{
				//Change a Existing Descriptor
				ChangeEnvironmentDescriptor(i);
				flagIsChange = true;
				OutResponse.bSucceed = true;
				break;
			}
		}

		if (!flagIsChange)
		{
			//Add a new Descriptor to array
			FUAVGEnvironmentDescriptor ToAdd;
			ToAdd.Descriptor = LastNodeResponse.EnvironmentToAdd;
			ToAdd.AdditonalArguments = LastNodeResponse.AdditonalEnvironmentArguments;
			EnvironmentDescriptor.Add(ToAdd);
			IUAVGActorInterface::Execute_OnEnvironmentDescriptorAdded(ActorInterface, ToAdd, EnvironmentDescriptor);
			IUAVGUIInterface::Execute_OnEnvironmentDescriptorAdded(UIInterface, ToAdd, EnvironmentDescriptor);
			OutResponse.bSucceed = true;
		}
	}

	if (LastNodeResponse.EnvironmentsToRemove.Num() > 0)
	{
		TArray<FUAVGEnvironmentDescriptor> Removed;
		for (const FString& DesStr : LastNodeResponse.EnvironmentsToRemove)
		{
			//maybe better ways?
			for (int32 i = 0; i < EnvironmentDescriptor.Num(); ++i)
			{
				if (EnvironmentDescriptor[i].Descriptor == DesStr)
				{
					Removed.Add(EnvironmentDescriptor[i]);
					EnvironmentDescriptor.RemoveAt(i);
				}
			}
		}
		IUAVGActorInterface::Execute_OnEnvironmentDescriptorRemoved(ActorInterface, Removed, EnvironmentDescriptor);
		IUAVGUIInterface::Execute_OnEnvironmentDescriptorRemoved(UIInterface, Removed, EnvironmentDescriptor);
		OutResponse.bSucceed = true;
	}

	FUAVGComponentNextResponse Response;
	NextNode(Response);

	OutResponse.bSucceed = OutResponse.bSucceed && Response.bSucceed;
}

void UUAVGComponent::OnReachRunSubScriptNode(FUAVGComponentNextResponse& OutResponse)
{
	if(!LastNodeResponse.SubScriptToRun)
	{
		UE_LOG(LogUAVGRuntimeComponent, Error, TEXT("RunSubScriptNode SubScript Empty!"));
		OutResponse.bSucceed = false;
		return;
	}
	
	ScriptStack.Push(MyScript);
	CurrentNodeStack.Push(CurrentNode);
	LastNodeStack.Push(LastNode);
	
	MyScript = LastNodeResponse.SubScriptToRun;
	CurrentNode = Cast<UUAVGScriptRuntimeNode>(MyScript->GetRuntimeRootNode());
	
	FUAVGComponentNextResponse R;
	NextNode(R);
	
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

void UUAVGComponent::WarpSaveObject(UUAVGSaveGame* InSave)
{
	if (!InSave)
		return;

	InSave->MyScript = MyScript;
	InSave->CurrentNode = CurrentNode;
	InSave->LastNode = LastNode;
	InSave->EnvironmentDescriptor = EnvironmentDescriptor;
	InSave->ScriptStack = ScriptStack;
	InSave->CurrentNodeStack = CurrentNodeStack;
	InSave->LastNodeStack = LastNodeStack;
}

void UUAVGComponent::UnWarpSaveObject(UUAVGSaveGame* InSave)
{
	if (!InSave)
		return;

	CurrentNode = InSave->CurrentNode;
	LastNode = InSave->LastNode;
	ScriptStack = InSave->ScriptStack;
	CurrentNodeStack = InSave->CurrentNodeStack;
	LastNodeStack = InSave->LastNodeStack;
	UnWarpEnvironmentDescriptor(InSave->EnvironmentDescriptor);
}

void UUAVGComponent::UnWarpEnvironmentDescriptor(TArray<FUAVGEnvironmentDescriptor> SavedDescriptor)
{
	for (FUAVGEnvironmentDescriptor NewDes : SavedDescriptor)
	{
		EnvironmentDescriptor.Add(NewDes);

		IUAVGActorInterface::Execute_OnEnvironmentDescriptorAdded(ActorInterface, NewDes, EnvironmentDescriptor);
		IUAVGUIInterface::Execute_OnEnvironmentDescriptorAdded(UIInterface, NewDes, EnvironmentDescriptor);
	}
}

void UUAVGComponent::ChangeEnvironmentDescriptor(int32 IndexToChange)
{
	if (EnvironmentDescriptor.IsValidIndex(IndexToChange))
	{
		FUAVGEnvironmentDescriptor OldDescriptor = EnvironmentDescriptor[IndexToChange];//Cache the old one(Not Reference)
		EnvironmentDescriptor[IndexToChange].AdditonalArguments = LastNodeResponse.AdditonalEnvironmentArguments;

		IUAVGActorInterface::Execute_OnEnvironmentDescriptorChanged(ActorInterface, OldDescriptor, EnvironmentDescriptor[IndexToChange], EnvironmentDescriptor);
		IUAVGUIInterface::Execute_OnEnvironmentDescriptorChanged(UIInterface, OldDescriptor, EnvironmentDescriptor[IndexToChange], EnvironmentDescriptor);
	}
}
