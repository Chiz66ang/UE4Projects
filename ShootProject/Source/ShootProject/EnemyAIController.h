// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootProject.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virtual void Possess(APawn* InPawn) override;

	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName IsInAttackRange;
	//virtual void UnPossess() override;
	

private:
	UPROPERTY()
		class UBehaviorTree* BTAsset;

	UPROPERTY()
		class UBlackboardData* BBAsset;
	/*
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;
	float RepeatInterval;
	*/
	
};
