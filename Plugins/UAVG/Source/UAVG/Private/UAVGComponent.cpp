//NTRHostage

#include "UAVGComponent.h"

#include "IUAVGActorInterface.h"
#include "IUAVGUIInterface.h"
#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"
#include "UAVGScriptRTNodeSaySingle.h"

UUAVGComponent::UUAVGComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUAVGComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!(MyScript && UIInterface && ActorInterface)) return;

	switch (GetUAVGState())
	{
	case EUAVGRuntimeState::URS_Speaking:
		Speak();
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

void UUAVGComponent::NextLine(FUAVGComponentNextRespose& OutResponse)
{
	LastNode = CurrentNode;
	CurrentNode = CurrentNode->GetNextNode();
	if (CurrentNode == nullptr)
	{
		//We Reached the End of Script
		CurrentState = EUAVGRuntimeState::URS_Finished;
		OutResponse.bSucceed = true;
		return;
	}
	FUAVGScriptRuntimeNodeArriveResponse ArriveResponse = CurrentNode->OnArrive();
	if(ArriveResponse.bShouldUpdateDesiredTexts)
		DesiredText = ArriveResponse.DesiredTexts;
	OutResponse.bSucceed = true;
	CurrentState = EUAVGRuntimeState::URS_Speaking;
}

void UUAVGComponent::Speak()
{
	if (DesiredText.Num() <= 0) return;

	//TODO Speak Character by Character.
	IUAVGActorInterface::Execute_OnNewLine(ActorInterface, FUAVGActorLineInfo(DesiredText));
	IUAVGUIInterface::Execute_OnNewLine(UIInterface, FUAVGUILineInfo(DesiredText));
	for (int32 i = 0; i < DesiredText.Num(); ++i)
	{
		IUAVGActorInterface::Execute_OnTextUpdated(ActorInterface, i, DesiredText[i].TextLine);
		IUAVGUIInterface::Execute_OnTextUpdated(UIInterface, i, DesiredText[i].TextLine);
	}
	CurrentState = EUAVGRuntimeState::URS_ReadyForNext;
}
