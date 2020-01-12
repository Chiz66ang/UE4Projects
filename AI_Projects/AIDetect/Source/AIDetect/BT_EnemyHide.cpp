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
	
	//적 입장에서 가장 가까운 엄폐물 찾기
	for (int i = 0; i < Actors.Num(); i++)
	{
		if (Enemy->GetDistanceTo(min) >= Enemy->GetDistanceTo(Actors[i]))
		{
			min = Actors[i];
		};
	}
	//min = 가장 가까운 액터
	

	//캐릭터를 반대 방향으로 하는 단위 백터
	FVector normVec = (min->GetActorLocation() - Player->GetActorLocation()).GetSafeNormal();
	
	//대충 액터의 범위를 곱해준 백터
	FVector Vec(normVec.X * 150.0F, normVec.Y * 150.0F, normVec.Z * 1.0F);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), Vec.X, Vec.Y, Vec.Z);
	//범위를 곱해준 백터에 액터 로케이션 더해주기.
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
