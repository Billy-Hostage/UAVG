//NTRHostage

#include "UAVGActor.h"
#include "UAVGScript.h"

FUAVGActorNextResponse::FUAVGActorNextResponse()
{

}

FUAVGActorTickInfo::FUAVGActorTickInfo()
{
	DisplayStringArray.Empty();
}

AUAVGActor::AUAVGActor()
{

}

void AUAVGActor::Tick(float DeltaSeconds)
{
	if (MyScript)
		MyScript->TickUAVGScript(this);
	Super::Tick(DeltaSeconds);

	FUAVGActorTickInfo Info;

	UAVGTick(Info);
}

FUAVGActorNextResponse AUAVGActor::Next()
{
	FUAVGActorNextResponse Return;

	MyScript->UAVGScriptNext(Return);

	return Return;
}

void AUAVGActor::ResetProgress()
{
	MyScript->ResetScriptProgress();
}
