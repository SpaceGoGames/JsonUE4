// Copyright Playspace S.L. 2017

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "JsonTypes.h"
#include "JsonItemBP.h"
#include "JsonArrayBP.generated.h"

class UJsonValueBP;

UCLASS(BlueprintType, Blueprintable)
class JSONUE4_API UJsonArrayBP : public UJsonItemBP
{
	GENERATED_BODY()
public:
	UJsonArrayBP();

	/** Clear the whole object */
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual void Clear() override;

	virtual bool SetValue(FJsonValuePtr JsonValue) override;
	FJsonValuePtr GetValue();

	/** Encode into a JSON string*/
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual FString Encode(bool bPretty = false) const override;

	/** Decode from a JSON string */
	UFUNCTION(BlueprintCallable, Category = "Json")
	virtual bool Decode(const FString& JsonString) override;

	/** Get the JsonValue as an array */
	UFUNCTION(BlueprintCallable, Category = "Json")
	TArray<UJsonItemBP*> GetArray() const;

private:
	FJsonValuePtr JsonValuePtr;
};
