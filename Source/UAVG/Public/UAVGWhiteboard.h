//NTRHostage

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UAVGWhiteboard.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUAVGWhiteboard, Log, All);

/**
 * This object is used to save all variables in scripts
 */
UCLASS(BlueprintType)
class UAVG_API UUAVGWhiteboard : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	void SetStringVariable(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	FString GetRawVariableConstRef(const FString& Key) const;

	// This is used for a custom save/load system
	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	TMap<FString, FString> FetchVariablesMap() const;

	UFUNCTION(BlueprintCallable, Category = "UAVG|Whiteboard")
	void InitWithVariables(const TMap<FString, FString>& NewVariables);
protected:
	UPROPERTY()
	TMap<FString, FString> Variables;
};
