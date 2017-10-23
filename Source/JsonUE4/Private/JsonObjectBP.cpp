// Copyright Playspace S.L. 2017

#include "JsonObjectBP.h"
#include "JsonValueBP.h"
#include "JsonTypes.h"
#include "JsonFactory.h"
#include "Serialization/JsonSerializer.h"

//
// JsonObject Wrapper
//

UJsonObjectBP::UJsonObjectBP()
	: Super()
{
}

void UJsonObjectBP::Clear()
{
	if (JsonPtr.IsValid())
	{
		JsonPtr.Reset();
	}
	JsonPtr = MakeShareable(new FJsonObject());
}

bool UJsonObjectBP::SetValue(FJsonValuePtr JsonValue)
{
	if (JsonValue.IsValid() && JsonValue->Type == EJson::Object)
	{
		SetObject(JsonValue->AsObject());
		return true;
	}
	return false;
}

TSharedPtr<FJsonObject> UJsonObjectBP::GetObject()
{
	return JsonPtr;
}

void UJsonObjectBP::SetObject(TSharedPtr<FJsonObject> JsonObject)
{
	JsonPtr = JsonObject;
}

FString UJsonObjectBP::Encode(bool bPretty /* = false*/) const
{
	if (!JsonPtr.IsValid())
	{
		return TEXT("{}");
	}

	FString OutputString;
	if (bPretty)
	{
		auto Writer = FPrettyJsonStringWriterFactory::Create(&OutputString);
		FJsonSerializer::Serialize(JsonPtr.ToSharedRef(), Writer);
	}
	else
	{
		auto Writer = FCondensedJsonStringWriterFactory::Create(&OutputString);
		FJsonSerializer::Serialize(JsonPtr.ToSharedRef(), Writer);
	}

	return OutputString;
}

bool UJsonObjectBP::Decode(const FString& JsonString)
{
	auto Reader = TJsonReaderFactory<>::Create(*JsonString);
	if (FJsonSerializer::Deserialize(Reader, JsonPtr) && JsonPtr.IsValid())
	{
		return true;
	}
	Clear();
	UE_LOG(LogJsonUE4, Error, TEXT("Failed to decode Object from JSON string for: %s"), *JsonString);
	return false;
}

TArray<FString> UJsonObjectBP::GetKeys() const
{
	TArray<FString> Result;
	if (JsonPtr.IsValid())
	{
		JsonPtr->Values.GetKeys(Result);
	}
	return Result;
}

int32 UJsonObjectBP::Num() const
{
	return JsonPtr.IsValid() ? JsonPtr->Values.Num() : -1;
}

bool UJsonObjectBP::HasField(const FString& FieldName) const
{
	return JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasField(FieldName);
}

void UJsonObjectBP::RemoveField(const FString& FieldName)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->RemoveField(FieldName);
	}
}

UJsonValueBP* UJsonObjectBP::GetField(const FString& FieldName) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TSharedPtr<FJsonValue> NewVal = JsonPtr->TryGetField(FieldName);
		if (NewVal.IsValid())
		{
			UJsonValueBP* NewValue = NewObject<UJsonValueBP>();
			NewValue->SetValue(NewVal);

			return NewValue;
		}
	}
	return nullptr;
}

UJsonValueBP* UJsonObjectBP::GetFieldRecursive(const FString& FieldName)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TArray<FString> KeyList;
		FieldName.ParseIntoArray(KeyList, TEXT("."), true);

		TSharedPtr<FJsonValue> CurrentObj = MakeShareable(new FJsonValueObject(JsonPtr));
		for (auto i = 0; i < KeyList.Num(); i++)
		{
			auto CurrentName = KeyList[i];
			auto Field = JsonPtr->TryGetField(CurrentName);
			if (Field.IsValid())
			{
				CurrentObj = Field;
			}
			else
			{
				return nullptr;
			}
		}
		if (CurrentObj.IsValid())
		{
			UJsonValueBP* NewValue = NewObject<UJsonValueBP>();
			NewValue->SetValue(CurrentObj);
			return NewValue;
		}
	}
	return nullptr;
}

void UJsonObjectBP::SetField(const FString& FieldName, UJsonValueBP* JsonValue)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->SetField(FieldName, JsonValue->GetValue());
	}
}

UJsonValueBP* UJsonObjectBP::AsValue() const
{
	if (JsonPtr.IsValid())
	{
		auto newValue = NewObject<UJsonValueBP>();
		FJsonValuePtr jsonValue = MakeShareable(new FJsonValueObject(JsonPtr));
		newValue->SetValue(jsonValue);
		return newValue;
	}
	return nullptr;
}

float UJsonObjectBP::GetFloat(const FString& FieldName, float DefaultValue) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Number>(FieldName))
	{
		return JsonPtr->GetNumberField(FieldName);
	}

	UE_LOG(LogJsonUE4, Warning, TEXT("No field with name %s of type Number"), *FieldName);
	return DefaultValue;
}

UJsonObjectBP* UJsonObjectBP::SetFloat(const FString& FieldName, float Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->SetNumberField(FieldName, Value);
	}
	return this;
}

int32 UJsonObjectBP::GetInt(const FString& FieldName, int32 DefaultValue) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Number>(FieldName))
	{
		return JsonPtr->GetIntegerField(FieldName);
	}

	UE_LOG(LogJsonUE4, Warning, TEXT("No field with name %s of type Number"), *FieldName);
	return DefaultValue;
}

UJsonObjectBP* UJsonObjectBP::SetInt(const FString& FieldName, int32 Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->SetNumberField(FieldName, Value);
	}
	return this;
}

FString UJsonObjectBP::GetString(const FString& FieldName, const FString& DefaultValue) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::String>(FieldName))
	{
		return JsonPtr->GetStringField(FieldName);
	}

	UE_LOG(LogJsonUE4, Warning, TEXT("No field with name %s of type String"), *FieldName);
	return DefaultValue;
}

UJsonObjectBP* UJsonObjectBP::SetString(const FString& FieldName, const FString& Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->SetStringField(FieldName, Value);
	}
	return this;
}

bool UJsonObjectBP::GetBool(const FString& FieldName, bool DefaultValue) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Boolean>(FieldName))
	{
		return JsonPtr->GetBoolField(FieldName);
	}

	UE_LOG(LogJsonUE4, Warning, TEXT("No field with name %s of type Bool"), *FieldName);
	return DefaultValue;
}

UJsonObjectBP* UJsonObjectBP::SetBool(const FString& FieldName, bool Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		JsonPtr->SetBoolField(FieldName, Value);
	}
	return this;
}

UJsonObjectBP* UJsonObjectBP::GetObject(const FString& FieldName, UJsonObjectBP* DefaultValue) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Object>(FieldName))
	{
		auto JsonObjField = JsonPtr->GetObjectField(FieldName);
		auto JsonObj = NewObject<UJsonObjectBP>();
		JsonObj->SetObject(JsonObjField);
		return JsonObj;
	}

	UE_LOG(LogJsonUE4, Warning, TEXT("No field with name %s of type JsonObject"), *FieldName);
	return DefaultValue;
}

UJsonObjectBP* UJsonObjectBP::SetObject(const FString& FieldName, UJsonObjectBP* Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && Value != nullptr)
	{
		JsonPtr->SetObjectField(FieldName, Value->GetObject());
	}
	return this;
}

TArray<float> UJsonObjectBP::GetFloatArray(const FString& FieldName) const
{
	TArray<float> Result;
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Array>(FieldName))
	{
		auto JsonArrayValues = JsonPtr->GetArrayField(FieldName);
		for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
		{
			auto Value = (*It).Get();
			if (Value->Type != EJson::Number)
			{
				UE_LOG(LogJsonUE4, Error, TEXT("NAN item in array %s"), *FieldName);
				continue;
			}

			Result.Add((*It)->AsNumber());
		}
	}
	return Result;
}

void UJsonObjectBP::SetFloatArray(const FString& FieldName, const TArray<float>& Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TArray< TSharedPtr<FJsonValue> > EntriesArray;
		for (auto Number : Value)
		{
			EntriesArray.Add(MakeShareable(new FJsonValueNumber(Number)));
		}
		JsonPtr->SetArrayField(FieldName, EntriesArray);
	}
}

TArray<FString> UJsonObjectBP::GetStringArray(const FString& FieldName) const
{
	TArray<FString> Result;
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Array>(FieldName))
	{
		auto JsonArrayValues = JsonPtr->GetArrayField(FieldName);
		for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
		{
			auto Value = (*It).Get();
			if (Value->Type != EJson::String)
			{
				UE_LOG(LogJsonUE4, Error, TEXT("Non string item in array %s"), *FieldName);
				continue;
			}

			Result.Add((*It)->AsString());
		}		
	}
	return Result;
}

void UJsonObjectBP::SetStringArray(const FString& FieldName, const TArray<FString>& Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TArray< TSharedPtr<FJsonValue> > EntriesArray;
		for (auto String : Value)
		{
			EntriesArray.Add(MakeShareable(new FJsonValueString(String)));
		}
		JsonPtr->SetArrayField(FieldName, EntriesArray);
	}
}

TArray<bool> UJsonObjectBP::GetBoolArray(const FString& FieldName) const
{
	TArray<bool> Result;
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Array>(FieldName))
	{
		auto JsonArrayValues = JsonPtr->GetArrayField(FieldName);
		for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
		{
			auto Value = (*It).Get();
			if (Value->Type != EJson::Boolean)
			{
				UE_LOG(LogJsonUE4, Error, TEXT("Non bool item in array %s"), *FieldName);
				continue;
			}

			Result.Add((*It)->AsBool());
		}		
	}
	return Result;
}

void UJsonObjectBP::SetBoolArray(const FString& FieldName, const TArray<bool>& Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TArray< TSharedPtr<FJsonValue> > EntriesArray;
		for (auto Bool : Value)
		{
			EntriesArray.Add(MakeShareable(new FJsonValueBoolean(Bool)));
		}
		JsonPtr->SetArrayField(FieldName, EntriesArray);
	}
}

TArray<UJsonObjectBP*> UJsonObjectBP::GetObjectArray(const FString& FieldName) const
{
	TArray<UJsonObjectBP*> Result;
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && JsonPtr->HasTypedField<EJson::Array>(FieldName))
	{
		auto JsonArrayValues = JsonPtr->GetArrayField(FieldName);
		for (TArray<TSharedPtr<FJsonValue> >::TConstIterator It(JsonArrayValues); It; ++It)
		{
			auto Value = (*It).Get();
			if (Value->Type != EJson::Object)
			{
				UE_LOG(LogJsonUE4, Error, TEXT("Non JsonObject item in array %s"), *FieldName);
				continue;
			}

			auto JsonObjField = Value->AsObject();
			auto JsonObj = NewObject<UJsonObjectBP>();
			JsonObj->SetObject(JsonObjField);

			Result.Add(JsonObj);
		}
	}
	return Result;
}

void UJsonObjectBP::SetObjectArray(const FString& FieldName, const TArray<UJsonObjectBP*>& Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{
		TArray< TSharedPtr<FJsonValue> > EntriesArray;
		for (auto Object : Value)
		{
			EntriesArray.Add(MakeShareable(new FJsonValueObject(Object->GetObject())));
		}
		JsonPtr->SetArrayField(FieldName, EntriesArray);
	}
}

UJsonArrayBP* UJsonObjectBP::GetArray(const FString& FieldName) const
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty())
	{

		TSharedPtr<FJsonValue> NewVal = JsonPtr->TryGetField(FieldName);
		if (NewVal.IsValid() && NewVal->Type == EJson::Array)
		{
			auto newArray = UJsonFactory::NewJsonArray();
			newArray->SetValue(NewVal);
			return newArray;
		}
	}
	return nullptr;
}

void UJsonObjectBP::SetArray(const FString& FieldName, UJsonArrayBP* Value)
{
	if (JsonPtr.IsValid() && !FieldName.IsEmpty() && Value->GetValue().IsValid())
	{
		JsonPtr->SetArrayField(FieldName, Value->GetValue()->AsArray());
	}
}