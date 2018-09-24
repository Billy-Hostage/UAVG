//NTRHostage Coded

#include "UAVGScript.h"
#include "UAVGScriptRTNodeRoot.h"
#include "UAVGActor.h"

DEFINE_LOG_CATEGORY(LogUAVGRuntimeScript);

UUAVGScript::UUAVGScript()
{
}

void UUAVGScript::TickUAVGScript(AUAVGActor* Ticker)
{
	if (CurrentStatus == EUAVGScriptStatus::Speaking)
	{
		//TODO Spaeking Here
	}
}

void UUAVGScript::UAVGScriptNext(FUAVGActorNextResponse& InResponse)
{
	switch (CurrentStatus)
	{
	case EUAVGScriptStatus::ReadyForNext:
		//Goto Next Node Here
		InResponse.Type = EUAVGActorNextResponseType::Success;
		break;
	default:
		InResponse.Type = EUAVGActorNextResponseType::Failed;
		break;
	}
}

UUAVGScriptRuntimeNodeRoot* UUAVGScript::SetupNewRuntimeScript()
{
	RootNode = NewObject<UUAVGScriptRuntimeNodeRoot>(this, UUAVGScriptRuntimeNodeRoot::StaticClass(), NAME_None, RF_Transactional);
	AllNodes.Empty();
	AddRuntimeNode(RootNode);
	CurrentNode = Cast<UUAVGScriptRuntimeNode>(RootNode);
	CurrentStatus = EUAVGScriptStatus::ReadyForNext;
	return RootNode;
}

bool UUAVGScript::AddRuntimeNode(UUAVGScriptRuntimeNode* NewNode)
{
	AllNodes.AddUnique(NewNode);
	return true;
}

const FText& UUAVGScript::TestScript()
{
	if (RootNode)
	{
		UE_LOG(LogUAVGRuntimeScript, Warning, TEXT("Found Root Node. The Script's Name is '%s_%s' "), *GetName(), *(RootNode->ScriptName.ToString()));
	}
	else
	{
		UE_LOG(LogUAVGRuntimeScript, Error, TEXT("NO ROOT NODE FOUND ! Try To Save Script '%s' !"), *GetName());
		return FText::GetEmpty();
	}

	//temporary testing code
	UUAVGScriptRuntimeNodeSaySingle* SaySingleNode = Cast<UUAVGScriptRuntimeNodeSaySingle>(RootNode->MyChildNodes[0]);
	if (!SaySingleNode) return FText::GetEmpty();
	return SaySingleNode->SaySingleText;
}
