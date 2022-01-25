// Copyright Epic Games, Inc. All Rights Reserved.

#include "TelekinesisPrototypeGameMode.h"
#include "TelekinesisPrototypeHUD.h"
#include "TelekinesisPrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATelekinesisPrototypeGameMode::ATelekinesisPrototypeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATelekinesisPrototypeHUD::StaticClass();
}
