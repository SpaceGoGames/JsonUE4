// Copyright Playspace S.L. 2017

#include "JsonArrayBP.h"
#include "JsonValueBP.h"
#include "JsonTypes.h"
#include "Serialization/JsonSerializer.h"
#include "JsonFactory.h"

//
// JsonObject Wrapper
//

UJsonArrayBP::UJsonArrayBP()
	: Super()
{
}

void UJsonArrayBP::Clear()
{
	if (JsonValuePtr.IsValid())
	{
		JsonValuePtr.Reset();
	}
}

bool UJsonArrayBP::SetValue(FJsonValuePtr JsonValue)
{
	if (JsonValue.IsValid() && JsonValue->Type == EJson::Array)
	{
		JsonValuePtr = JsonValue;
		return true;
	}
	return false;
}

FJsonValuePtr UJsonArrayBP::GetValue()
{
	return JsonValuePtr;
}

FString UJsonArrayBP::Encode(bool bPretty /* = false*/) const
{
	if (!JsonValuePtr.IsValid())
	{
		return TEXT("[]");
	}

	FString OutputString;
	if (bPretty)
	{
		auto Writer = FPrettyJsonStringWriterFactory::Create(&OutputString);
		FJsonSerializer::Serialize(JsonValuePtr->AsArray(), Writer);
	}
	else
	{
		auto Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
		FJsonSerializer::Serialize(JsonValuePtr->AsArray(), Writer);
	}

	return OutputString;
}

bool UJsonArrayBP::Decode(const FString& JsonString)
{
	auto Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonValuePtr NewJsonValuePtr;
	if (FJsonSerializer::Deserialize(Reader, NewJsonValuePtr) && NewJsonValuePtr.IsValid() && NewJsonValuePtr->Type == EJson::Array)
	{
		SetValue(NewJsonValuePtr);
		return true;
	}
	Clear();
	UE_LOG(LogJsonUE4, Error, TEXT("Failed to decode Array from JSON string for: %s"), *JsonString);
	return false;
}

TArray<UJsonItemBP*> UJsonArrayBP::GetArray() const
{
	TArray<UJsonItemBP*> Result;
	if (JsonValuePtr.IsValid())
	{
		auto Values = JsonValuePtr->AsArray();
		for (auto Value : Values)
		{
			auto Item = UJsonFactory::NewJsonItem(Value);
			if (Item != nullptr)
			{
				Result.Add(Item);
			}
		}
	}
	return Result;
}
