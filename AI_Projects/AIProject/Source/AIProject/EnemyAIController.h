// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIProject.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AIPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
};
