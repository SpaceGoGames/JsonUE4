// Copyright Playspace S.L. 2017
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "JsonUE4Globals.h"
#include "JsonTypes.h"
#include "JsonObjectBP.h"
#include "JsonArrayBP.h"
#include "JsonValueBP.generated.h"


class UJsonObjectBP;

UCLASS(BlueprintType, Blueprintable)
class JSONUE4_API UJsonValueBP : public UObject
{
	GENERATED_BODY()
public:
	UJsonValueBP();

	FJsonValuePtr& GetValue();
	void SetValue(FJsonValuePtr& JsonValue);

	//
	// JSON API
	//

	/** Type of value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	EJsonType GetType() const;

	/** Type of value */
	UFUNCTION(BlueprintCallable, Category = "Json")
	FName GetTypeAsName() const;

	/** Ceck if the type is of value None */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsNone() const;

	/** Ceck if the type is of value Null */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsNull() const;

	/** Ceck if the type is of value String */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsString() const;

	/** Ceck if the type is of value Number */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsNumber() const;

	/** Ceck if the type is of value Boolean */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsBool() const;

	/** Ceck if the type is of value Array */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsArray() const;

	/** Ceck if the type is of value JsonObject */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool IsObject() const;

	/** Get the JsonValue as a string */
	UFUNCTION(BlueprintCallable, Category = "Json")
	FString AsString() const;

	/** Get the JsonValue as a number */
	UFUNCTION(BlueprintCallable, Category = "Json")
	float AsNumber() const;

	/** Get the JsonValue as a boolean */
	UFUNCTION(BlueprintCallable, Category = "Json")
	bool AsBool() const;

	/** Get the JsonValue as an array */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonArrayBP* AsArray() const;

	/** Get the JsonValue as an object */
	UFUNCTION(BlueprintCallable, Category = "Json")
	UJsonObjectBP* AsObject() const;

private:
	FJsonValuePtr JsonPtr;
};
