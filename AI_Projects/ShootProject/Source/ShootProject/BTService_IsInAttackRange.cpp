// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_IsInAttackRange.h"
#include "EnemyAIController.h"
#include "ShootProjectCharacter.h"
//#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_IsInAttackRange::UBTService_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
	Interval = 0.5F;
}

void UBTService_IsInAttackRange::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return;

	auto Target = Cast<AShootProjectCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetKey));
	if (nullptr == Target)
		return;

	bool bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0F);
	
		//IsInAttackRange
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsInAttackRange"), bResult);
	
}