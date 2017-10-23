// Copyright Playspace S.L. 2017

#include "JsonValueBP.h"
#include "JsonObjectBP.h"
#include "JsonFactory.h"

//
// JsonValue Wrapper
//

UJsonValueBP::UJsonValueBP()
	: Super()
{
	
}

TSharedPtr<FJsonValue>& UJsonValueBP::GetValue()
{
	return JsonPtr;
}

void UJsonValueBP::SetValue(TSharedPtr<FJsonValue>& JsonValue)
{
	JsonPtr = JsonValue;
}

EJsonType UJsonValueBP::GetType() const
{
	if (JsonPtr.IsValid())
	{
		switch (JsonPtr->Type)
		{
		case EJson::None: return EJsonType::None;
		case EJson::Null: return EJsonType::Null;
		case EJson::String: return EJsonType::String;
		case EJson::Number: return EJsonType::Number;
		case EJson::Boolean: return EJsonType::Boolean;
		case EJson::Array: return EJsonType::Array;
		case EJson::Object: return EJsonType::Object;
		default: return EJsonType::None;
		}
	}
	return EJsonType::None;
}

FName UJsonValueBP::GetTypeAsName() const
{
	static FName NoneName("None");
	static FName NullName("Null");
	static FName StringName("String");
	static FName NumberName("Number");
	static FName BooleanName("Boolean");
	static FName ArrayName("Array");
	static FName ObjectName("Object");
	if (JsonPtr.IsValid())
	{
		switch (JsonPtr->Type)
		{
		case EJson::None: return NoneName;
		case EJson::Null: return NullName;
		case EJson::String: return StringName;
		case EJson::Number: return NumberName;
		case EJson::Boolean: return BooleanName;
		case EJson::Array: return ArrayName;
		case EJson::Object: return ObjectName;
		default: return NoneName;
		}
	}	
	return NoneName;
}

bool UJsonValueBP::IsNone() const
{
	return !JsonPtr.IsValid() || JsonPtr->Type == EJson::None;
}

bool UJsonValueBP::IsNull() const
{
	return !JsonPtr.IsValid() || JsonPtr->IsNull();
}

bool UJsonValueBP::IsString() const
{
	return JsonPtr.IsValid() && JsonPtr->Type == EJson::String;
}

bool UJsonValueBP::IsNumber() const
{
	return JsonPtr.IsValid() && JsonPtr->Type == EJson::Number;
}

bool UJsonValueBP::IsBool() const
{
	return JsonPtr.IsValid() && JsonPtr->Type == EJson::Boolean;
}

bool UJsonValueBP::IsArray() const
{
	return JsonPtr.IsValid() && JsonPtr->Type == EJson::Array;
}

bool UJsonValueBP::IsObject() const
{
	return JsonPtr.IsValid() && JsonPtr->Type == EJson::Object;
}

FString UJsonValueBP::AsString() const
{
	return JsonPtr.IsValid() ? JsonPtr->AsString() : FString();
}

float UJsonValueBP::AsNumber() const
{
	return JsonPtr.IsValid() ? JsonPtr->AsNumber() : 0.0f;
}

bool UJsonValueBP::AsBool() const
{
	return JsonPtr.IsValid() ? JsonPtr->AsBool() : false;
}

UJsonArrayBP* UJsonValueBP::AsArray() const
{
	TArray<UJsonValueBP*> Result;
	if (JsonPtr.IsValid() && IsArray())
	{
		auto NewJsonArray = UJsonFactory::NewJsonArray();
		NewJsonArray->SetValue(JsonPtr);
		return NewJsonArray;
	}
	return nullptr;
}

UJsonObjectBP* UJsonValueBP::AsObject() const
{
	if (JsonPtr.IsValid() && IsObject())
	{
		auto NewJsonObject = UJsonFactory::NewJsonObject();
		NewJsonObject->SetValue(JsonPtr);
		return NewJsonObject;
	}
	return nullptr;
}
