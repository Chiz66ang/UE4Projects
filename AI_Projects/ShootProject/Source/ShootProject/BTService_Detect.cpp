// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"
#include "EnemyAIController.h"
#include "ShootProjectCharacter.h"
//#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5F;

	//AC = Cast<AEnemyCharacter>()
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.0F;
	if (nullptr == World) return;
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel3,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2F);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			AShootProjectCharacter* PlayerCharacter = Cast<AShootProjectCharacter>(OverlapResult.GetActor());
			//AEnemyCharacter* PlayerCharacter = Cast<AEnemyCharacter>(OverlapResult.GetActor());
			if (PlayerCharacter && PlayerCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, PlayerCharacter);
			}
			
			
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, nullptr);
	}
	
}
