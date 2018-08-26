//NTRHostage Coded

#pragma once

#include "CoreMinimal.h"
#include "UAVGScript.generated.h"

UCLASS(Blueprintable)
class UAVG_API UUAVGScript : public UObject
{
	GENERATED_BODY()
public:
	UUAVGScript();
	
	UPROPERTY(EditDefaultsOnly, Category = "UAVGScript")
	FString Name;
};