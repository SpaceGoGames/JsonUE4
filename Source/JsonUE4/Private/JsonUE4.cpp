// Copyright Playspace S.L. 2017

#include "JsonUE4.h"
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "IJsonUE4.h"
#include "JsonUE4Globals.h"

DEFINE_LOG_CATEGORY(LogJsonUE4);

#define LOCTEXT_NAMESPACE "FJsonUE4"

class FJsonUE4 : public IJsonUE4
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override
	{

	}

	virtual void ShutdownModule() override
	{

	}
};

IMPLEMENT_MODULE(FJsonUE4, JsonUE4)

#undef LOCTEXT_NAMESPACE
