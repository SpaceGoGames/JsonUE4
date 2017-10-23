// Copyright Playspace S.L. 2017
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "JsonTypes.h"
#include "JsonItemBP.generated.h"

class UJsonValueBP;

UCLASS(BlueprintType, Blueprintable)
class JSONUE4_API UJsonItemBP : public UObject
{
	GENERATED_BODY()
public:
	UJsonItemBP();

	/** Clear the whole object */
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual void Clear();

	virtual bool SetValue(FJsonValuePtr JsonValue);

	/** Encode into a JSON string*/
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual FString Encode(bool bPretty = false) const;

	/** Decode from a JSON string */
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual bool Decode(const FString& JsonString);
};
