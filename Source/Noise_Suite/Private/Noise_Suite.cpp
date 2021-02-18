// Copyright Epic Games, Inc. All Rights Reserved.

#include "Noise_Suite.h"

#define LOCTEXT_NAMESPACE "FNoise_SuiteModule"

void FNoise_SuiteModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FNoise_SuiteModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNoise_SuiteModule, Noise_Suite)