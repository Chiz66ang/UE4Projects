// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_TurnToTarget.h"
#include "EnemyAIController.h"
#include "ShootProjectCharacter.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == EnemyCharacter) return EBTNodeResult::Failed;

	auto Target = Cast<AShootProjectCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetKey));
	if (nullptr == Target) return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - EnemyCharacter->GetActorLocation();
	LookVector.Z = 0.0F;
	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	EnemyCharacter->SetActorRotation(FMath::RInterpTo(EnemyCharacter->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 20.f));

	return EBTNodeResult::Succeeded;
}
