// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "AttackAnimGameMode.h"
#include "AttackAnimCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAttackAnimGameMode::AAttackAnimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
