// Copyright Playspace S.L. 2017
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "JsonTypes.h"
#include "JsonItemBP.h"
#include "JsonObjectBP.generated.h"

class UJsonValueBP;

UCLASS(BlueprintType, Blueprintable)
class JSONUE4_API UJsonObjectBP : public UJsonItemBP
{
	GENERATED_BODY()
public:
	UJsonObjectBP();

	/** Clear the whole object */
	virtual void Clear() override;

	virtual bool SetValue(FJsonValuePtr JsonValue) override;
	FJsonObjectPtr GetObject();
	void SetObject(FJsonObjectPtr JsonObject);

	/** Encode into a JSON string*/
	virtual FString Encode(bool bPretty = false) const override;

	/** Decode from a JSON string */
	virtual bool Decode(const FString& JsonString) override;

	//
	// JSON API
	//

	/** Returns the list of keys the JSON object holds */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<FString> GetKeys() const;

	/** Returns the number of keys the JSON object holds */
	UFUNCTION(BlueprintCallable, Category = "Json")
	int32 Num() const;

	UFUNCTION(BlueprintCallable, Category = "Json")
	bool HasField(const FString& FieldName) const;

	UFUNCTION(BlueprintCallable, Category = "Json")
	void RemoveField(const FString& FieldName);

	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonValueBP* GetField(const FString& FieldName) const;

	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonValueBP* GetFieldRecursive(const FString& FieldName);

	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetField(const FString& FieldName, UJsonValueBP* JsonValue);

	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonValueBP* AsValue() const;

	//
	// Field Access API
	//

	/** Set a Float value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	float GetFloat(const FString& FieldName, float DefaultValue) const;

	/** Get a float value */
	UFUNCTION(BlueprintCallable,  Category = "Json")
	UJsonObjectBP* SetFloat(const FString& FieldName, float Value);

	/** Get Int value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	int32 GetInt(const FString& FieldName, int32 DefaultValue) const;

	/** Set Int value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* SetInt(const FString& FieldName, int32 Value);

	/** Get String value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	FString GetString(const FString& FieldName, const FString& DefaultValue) const;

	/** Set String value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* SetString(const FString& FieldName, const FString& Value);

	/** Get bool value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool GetBool(const FString& FieldName, bool DefaultValue) const;

	/** Set bool value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* SetBool(const FString& FieldName, bool Value);

	/** Get JsonObject value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* GetObject(const FString& FieldName, UJsonObjectBP* DefaultValue) const;

	/** Set JsonObject value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* SetObject(const FString& FieldName, UJsonObjectBP* Value);

	//
	// Array properties
	//



	/** Get an array of float values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<float> GetFloatArray(const FString& FieldName) const;

	/** Set an array of float values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetFloatArray(const FString& FieldName, const TArray<float>& Value);

	/** Get an array of string values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<FString> GetStringArray(const FString& FieldName) const;

	/** Set an array of string values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetStringArray(const FString& FieldName, const TArray<FString>& Value);

	/** Get an array of bool values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<bool> GetBoolArray(const FString& FieldName) const;

	/** Set an array of bool values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetBoolArray(const FString& FieldName, const TArray<bool>& Value);

	/** Get an array of JsonObject values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<UJsonObjectBP*> GetObjectArray(const FString& FieldName) const;

	/** Set an array of JsonObject values */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetObjectArray(const FString& FieldName, const TArray<UJsonObjectBP*>& Value);

	/** Get a JsonArray object */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonArrayBP* GetArray(const FString& FieldName) const;

	/** Set a JsonArray object */
	UFUNCTION(BlueprintCallable, Category = "Json")
	void SetArray(const FString& FieldName, UJsonArrayBP* Value);

private:
	FJsonObjectPtr JsonPtr;
};
