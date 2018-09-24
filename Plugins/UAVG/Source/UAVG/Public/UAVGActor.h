//NTRHostge

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAVGActor.generated.h"

UCLASS()
class UAVG_API AUAVGActor : public AActor
{
	GENERATED_BODY()
public:
	AUAVGActor();

	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UAVG", meta = (DisplayName = "Script"))
	class UUAVGScript* MyScript = nullptr;
};
