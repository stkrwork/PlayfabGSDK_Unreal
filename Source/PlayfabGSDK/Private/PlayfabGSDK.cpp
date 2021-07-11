// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayfabGSDK.h"

#include "GSDKConfiguration.h"
#include "GSDKUtils.h"
#include "Misc/ScopeLock.h"

DEFINE_LOG_CATEGORY(LogPlayfabGSDK);

#define LOCTEXT_NAMESPACE "FPlayfabGSDKModule"

void FPlayfabGSDKModule::StartupModule()
{
		
}

void FPlayfabGSDKModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

bool FPlayfabGSDKModule::ReadyForPlayers()
{
	if (GSDKInternal->GetHeartbeatRequest().CurrentGameState != EGameState::Active)
	{
		GSDKInternal->SetState(EGameState::StandingBy);
		GSDKInternal->GetTransitionToActiveEvent()->Wait();
	}

	return GSDKInternal->GetHeartbeatRequest().CurrentGameState == EGameState::Active;
}

const FGameServerConnectionInfo FPlayfabGSDKModule::GetGameServerConnectionInfo()
{
	return GSDKInternal->GetConnectionInfo();
}

const TMap<FString, FString> FPlayfabGSDKModule::GetConfigSettings()
{
	return GSDKInternal->GetConfigSettings();
}

void FPlayfabGSDKModule::UpdateConnectedPlayers(const TArray<FConnectedPlayer>& currentlyConnectedPlayers)
{
}

uint32 FPlayfabGSDKModule::LogMessage(const FString& message)
{
	return 0;
}

const FString FPlayfabGSDKModule::GetLogsDirectory()
{
	FScopeLock ScopeLock(&GSDKInternal->GetConfigMutex());

	const TMap<FString, FString> Config = GSDKInternal->GetConfigSettings();

	if (Config.Contains(LOG_FOLDER_KEY))
	{
		return Config[LOG_FOLDER_KEY];
	}

	return TEXT("");
}

const FString FPlayfabGSDKModule::GetSharedContentDirectory()
{
	FScopeLock ScopeLock(&GSDKInternal->GetConfigMutex());

	const TMap<FString, FString> Config = GSDKInternal->GetConfigSettings();

	if (Config.Contains(SHARED_CONTENT_FOLDER_KEY))
	{
		return Config[SHARED_CONTENT_FOLDER_KEY];
	}

	return TEXT("");
}

const TArray<FString> FPlayfabGSDKModule::GetInitialPlayers()
{
	return GSDKInternal->GetInitialPlayers();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FPlayfabGSDKModule, PlayfabGSDK)