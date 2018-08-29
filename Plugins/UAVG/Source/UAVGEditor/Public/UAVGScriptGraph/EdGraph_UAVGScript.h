//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph_UAVGScript.generated.h"

UCLASS()
class UEdGraph_UAVGScript : public UEdGraph
{
	GENERATED_BODY()
public:
	UEdGraph_UAVGScript();
	virtual ~UEdGraph_UAVGScript();

	class UUAVGScript* GetUAVGScript() const;
};