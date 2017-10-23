// Copyright Playspace S.L. 2017
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonObjectBP.h"
#include "JsonItemBP.h"
#include "JsonArrayBP.h"
#include "JsonFactory.generated.h"

UCLASS()
class JSONUE4_API UJsonFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, meta = (DisplayName = "New Json Object", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UJsonObjectBP* NewJsonObject_K2(UObject* WorldContextObject);
	static UJsonObjectBP* NewJsonObject();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "New Json Object (From String)", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UJsonObjectBP* NewJsonObjectFromString_K2(UObject* WorldContextObject, const FString& JsonString);
	static UJsonObjectBP* NewJsonObjectFromString(const FString& JsonString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "New Json Array", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UJsonArrayBP* NewJsonArray_K2(UObject* WorldContextObject);
	static UJsonArrayBP* NewJsonArray();

	UFUNCTION(BlueprintPure, meta = (DisplayName = "New Json Array (From String)", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UJsonArrayBP* NewJsonArrayFromString_K2(UObject* WorldContextObject, const FString& JsonString);
	static UJsonArrayBP* NewJsonArrayFromString(const FString& JsonString);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Parse Json Item", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "Json")
	static UJsonItemBP* ParseJsonItem_K2(UObject* WorldContextObject, const FString& JsonString);
	static UJsonItemBP* ParseJsonItem(const FString& JsonString);

	static UJsonItemBP* NewJsonItem(FJsonValuePtr JsonValue, UObject* WorldContextObject = (UObject*)GetTransientPackage());
};

