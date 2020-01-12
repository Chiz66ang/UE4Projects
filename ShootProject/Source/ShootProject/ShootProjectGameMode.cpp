// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ShootProjectGameMode.h"
#include "ShootProjectHUD.h"
#include "ShootProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShootProjectGameMode::AShootProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShootProjectHUD::StaticClass();
}
