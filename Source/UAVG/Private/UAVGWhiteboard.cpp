//NTRHostage

#include "UAVGWhiteboard.h"

DEFINE_LOG_CATEGORY(LogUAVGWhiteboard);

void UUAVGWhiteboard::SetStringVariable(const FString& Key, const FString& Value)
{
	if (Variables.Contains(Key))
	{
		// update entry
		Variables[Key] = Value;
	}
	else
	{
		// new entry
		Variables.Add(Key, Value);
	}
}

FString UUAVGWhiteboard::GetRawVariableByKey(const FString& Key, bool bInitIfNotFound, const FString& InitValue)
{
	if (Variables.Contains(Key))
	{
		return Variables[Key];
	}
	else if (bInitIfNotFound)
	{
		Variables.Add(Key, InitValue);
		return InitValue;
	}
	else
	{
		UE_LOG(LogUAVGWhiteboard, Error, TEXT("Attempting to fetch a unset variable %s"), *Key);
		return FString::Printf(TEXT("UNSET VAR \"%s\""), *Key);
	}
}

bool UUAVGWhiteboard::ContainsVariable(const FString& Key) const
{
	return Variables.Contains(Key);
}

FString UUAVGWhiteboard::GetRawVariableConstRef(const FString& Key) const
{
	if (Variables.Contains(Key))
	{
		return Variables[Key];
	}
	else
	{
		UE_LOG(LogUAVGWhiteboard, Error, TEXT("Attempting to fetch a unset variable %s"), *Key);
		return FString::Printf(TEXT("UNSET VAR \"%s\""), *Key);
	}
}

TMap<FString, FString> UUAVGWhiteboard::FetchVariablesMap() const
{
	return Variables;
}

void UUAVGWhiteboard::InitWithVariables(const TMap<FString, FString>& NewVariables)
{
	if (Variables.Num() != 0)
	{
		UE_LOG(LogUAVGWhiteboard, Warning, TEXT("This will erase all present Variables!"));
	}

	Variables = NewVariables;
}
