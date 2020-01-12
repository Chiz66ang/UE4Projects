// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_EnemyHide.h"
#include "EnemyCharacter.h"
#include "AIDetectCharacter.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/TargetPoint.h"

UBT_EnemyHide::UBT_EnemyHide()
{
	NodeName = TEXT("FindHideVector");
}

EBTNodeResult::Type UBT_EnemyHide::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Actors);
	//UE_LOG(LogTemp, Warning, TEXT("ArryNum: %d"), Actors.Num());
	
	min = Actors[0];
	auto Enemy = OwnerComp.GetOwner();
	auto Player = OwnerComp.GetWorld()->GetFirstPlayerController()->GetCharacter();
	if(Player == nullptr) UE_LOG(LogTemp, Warning, TEXT("Player is null"));
	if(Enemy == nullptr) UE_LOG(LogTemp, Warning, TEXT("Enemy is null"));
	
	//�� ���忡�� ���� ����� ���� ã��
	for (int i = 0; i < Actors.Num(); i++)
	{
		if (Enemy->GetDistanceTo(min) >= Enemy->GetDistanceTo(Actors[i]))
		{
			min = Actors[i];
		};
	}
	//min = ���� ����� ����
	

	//ĳ���͸� �ݴ� �������� �ϴ� ���� ����
	FVector normVec = (min->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
	
	//���� ������ ������ ������ ����
	FVector Vec(normVec.X * 150.0F, normVec.Y * 150.0F, normVec.Z * 1.0F);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Vec.X, Vec.Y, Vec.Z);
	//������ ������ ���Ϳ� ���� �����̼� �����ֱ�.
	FVector Res = Vec + min->GetActorLocation();
	auto Leader = OwnerComp.GetAIOwner()->GetPawn();

	//FVector dis = min->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("ActorDistance: %f"), Enemy->GetDistanceTo(min));

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::HidePosKey, Res);

	if (Leader->ActorHasTag(FName(TEXT("TeamLeader"))))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TeamLeaderKey, Leader);
		UE_LOG(LogTemp, Warning, TEXT("TeamLeader in BB"));
	}
	
	return EBTNodeResult::Succeeded;
}
