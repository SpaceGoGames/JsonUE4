// Copyright Playspace S.L. 2017
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Dom/JsonValue.h"
#include "Dom/JsonObject.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonWriter.h"
#include "JsonTypes.generated.h"

typedef TJsonWriterFactory< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TCondensedJsonPrintPolicy<TCHAR> > FCondensedJsonStringWriter;

typedef TJsonWriterFactory< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > FPrettyJsonStringWriterFactory;
typedef TJsonWriter< TCHAR, TPrettyJsonPrintPolicy<TCHAR> > FPrettyJsonStringWriter;

typedef TSharedPtr<FJsonObject>	FJsonObjectPtr;
typedef TSharedPtr<FJsonValue>	FJsonValuePtr;

/** Enum to specify distortion mesh size */
UENUM()
enum class EJsonType : uint8
{
	None,
	Null,
	String,
	Number,
	Boolean,
	Array,
	Object
};

