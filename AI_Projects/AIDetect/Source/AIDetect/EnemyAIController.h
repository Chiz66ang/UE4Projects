// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIDetect.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class AIDETECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();
	virtual void Possess(APawn* InPawn) override;
	virtual void UnPossess() override;
	class AEnemyCharacter* Enemy;

	static const FName TargetPosKey;
	static const FName HidePosKey;
	static const FName bHearGunKey;
	static const FName LookPosKey;
	static const FName TeamLeaderKey;

	void MoveToTarget(FVector Location);
	void HearGunSound(bool heargun);
	void HearFootSound(FVector Location);

private:
	//void OnRepeatTimer();
	//FTimerHandle RepeatTimerHandle;
	//float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BTAsset;
	UPROPERTY()
		class UBlackboardData* BBAsset;
	
};
