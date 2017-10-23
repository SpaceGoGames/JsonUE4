// Copyright Playspace S.L. 2017

#include "JsonItemBP.h"
#include "JsonValueBP.h"
#include "JsonTypes.h"
#include "Serialization/JsonSerializer.h"

//
// JsonItem Wrapper
//

UJsonItemBP::UJsonItemBP()
	: Super()
{
	Clear();
}

void UJsonItemBP::Clear()
{

}

bool UJsonItemBP::SetValue(FJsonValuePtr JsonValue)
{
	return false;
}

FString UJsonItemBP::Encode(bool bPretty /* = false*/) const
{
	return FString();
}

bool UJsonItemBP::Decode(const FString& JsonString)
{
	Clear();
	UE_LOG(LogJsonUE4, Error, TEXT("Failed to decode from JSON string for: %s"), *JsonString);
	return false;
}