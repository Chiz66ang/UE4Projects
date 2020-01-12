// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
	IsAttacking = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	auto EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter)
		return EBTNodeResult::Failed;

	EnemyCharacter->Attack();
	EnemyCharacter->OnAttackEnd.AddLambda([this]()-> void {
		IsAttacking = false;
	});

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	if (!IsAttacking)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackEnd....."));
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
