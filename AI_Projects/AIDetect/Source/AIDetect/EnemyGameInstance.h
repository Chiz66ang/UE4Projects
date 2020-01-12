// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIDetect.h"
#include "Engine/GameInstance.h"
#include "EnemyGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FFoundPlayerDelegate)

/**
 * 
 */
UCLASS()
class AIDETECT_API UEnemyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	UEnemyGameInstance();

protected:
	virtual void Init() override;

public:
	void SetFoundPlayer(bool SeePlayer);
	bool FoundPlayer;
	TSubclassOf<AActor> EnemyChar;
	TArray<AActor*> EnemyArry;

	void SeePlayer();

};
