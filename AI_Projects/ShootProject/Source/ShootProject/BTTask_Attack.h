// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootProject.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Attack();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	bool IsAttacking = false;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
