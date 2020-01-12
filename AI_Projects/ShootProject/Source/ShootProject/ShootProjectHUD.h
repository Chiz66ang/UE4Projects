// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "ShootProject.h"
#include "GameFramework/HUD.h"
#include "ShootProjectHUD.generated.h"

UCLASS()
class AShootProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AShootProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

