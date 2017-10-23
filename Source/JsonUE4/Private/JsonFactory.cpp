// Copyright Playspace S.L. 2017

#include "JsonFactory.h"
#include "JsonObjectBP.h"
#include "JsonSerializer.h"
#include "JsonArrayBP.h"

//
// JsonFactory
//

UJsonObjectBP* UJsonFactory::NewJsonObject_K2(UObject* WorldContextObject)
{
	return NewObject<UJsonObjectBP>(WorldContextObject);
}

UJsonObjectBP* UJsonFactory::NewJsonObject()
{
	return NewObject<UJsonObjectBP>();
}

UJsonObjectBP* UJsonFactory::NewJsonObjectFromString_K2(UObject* WorldContextObject, const FString& JsonString)
{
	auto JsonObj = NewJsonObject_K2(WorldContextObject);
	JsonObj->Decode(JsonString);
	return JsonObj;
}

UJsonObjectBP* UJsonFactory::NewJsonObjectFromString(const FString& JsonString)
{
	auto JsonObj = NewJsonObject();
	JsonObj->Decode(JsonString);
	return JsonObj;
}

UJsonArrayBP* UJsonFactory::NewJsonArray_K2(UObject* WorldContextObject)
{
	return NewObject<UJsonArrayBP>(WorldContextObject);
}

UJsonArrayBP* UJsonFactory::NewJsonArray()
{
	return NewObject<UJsonArrayBP>();
}

UJsonArrayBP* UJsonFactory::NewJsonArrayFromString_K2(UObject* WorldContextObject, const FString& JsonString)
{
	auto JsonArray = NewJsonArray_K2(WorldContextObject);
	JsonArray->Decode(JsonString);
	return JsonArray;
}

UJsonArrayBP* UJsonFactory::NewJsonArrayFromString(const FString& JsonString)
{
	auto JsonArray = NewJsonArray();
	JsonArray->Decode(JsonString);
	return JsonArray;
}

UJsonItemBP* UJsonFactory::ParseJsonItem_K2(UObject* WorldContextObject, const FString& JsonString)
{
	auto Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonValuePtr JsonValuePtr;
	if (FJsonSerializer::Deserialize(Reader, JsonValuePtr) && JsonValuePtr.IsValid())
	{
		UJsonItemBP* item = nullptr;
		if (JsonValuePtr->Type == EJson::Object)
		{
			item = NewJsonObject_K2(WorldContextObject);
		}
		else if (JsonValuePtr->Type == EJson::Array)
		{
			item = NewJsonArray_K2(WorldContextObject);
		}

		if (item != nullptr)
		{
			item->SetValue(JsonValuePtr);
			return item;
		}
	}
	return nullptr;
}

UJsonItemBP* UJsonFactory::ParseJsonItem(const FString& JsonString)
{
	auto Reader = TJsonReaderFactory<>::Create(*JsonString);
	FJsonValuePtr JsonValuePtr;
	if (FJsonSerializer::Deserialize(Reader, JsonValuePtr) && JsonValuePtr.IsValid())
	{
		return NewJsonItem(JsonValuePtr);
	}
	return nullptr;
}

UJsonItemBP* UJsonFactory::NewJsonItem(FJsonValuePtr JsonValue, UObject* WorldContextObject /*= (UObject*)GetTransientPackage()*/)
{
	if (JsonValue.IsValid())
	{
		UJsonItemBP* Item = nullptr;
		if (JsonValue->Type == EJson::Object)
		{
			Item = NewJsonObject_K2(WorldContextObject);
		}
		else if (JsonValue->Type == EJson::Array)
		{
			Item = NewJsonArray_K2(WorldContextObject);
		}

		if (Item != nullptr)
		{
			Item->SetValue(JsonValue);
			return Item;
		}
	}
	return nullptr;
}
