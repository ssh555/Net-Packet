#include "nppch.h"
#if NP_UE_SUPPORT
// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetPacket.h"

#define LOCTEXT_NAMESPACE "FNetPacketModule"

void FNetPacketModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNetPacketModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNetPacketModule, NetPacket)
#endif