// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIDetect.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_EnemyHide.generated.h"

/**
 * 
 */
UCLASS()
class AIDETECT_API UBT_EnemyHide : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBT_EnemyHide();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	TArray<AActor*> Actors;

	AActor* min;

};
