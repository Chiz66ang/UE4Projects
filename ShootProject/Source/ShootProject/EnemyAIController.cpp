// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree//BlackboardComponent.h"
//#include "NavigationSystem.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName AEnemyAIController::HomePosKey(TEXT("HomePos"));
const FName AEnemyAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AEnemyAIController::TargetKey(TEXT("Target"));
const FName AEnemyAIController::IsInAttackRange(TEXT("IsInAttackRange"));

AEnemyAIController::AEnemyAIController()
{
	//RepeatInterval = 3.0F;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/BBAsset.BBAsset"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/BTAsset.BTAsset"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AEnemyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		if (!RunBehaviorTree(BTAsset))
		{
			UE_LOG(LogTemp, Warning, TEXT("AIController can't run BT!"));
		}
	}
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AEnemyAIController::OnRepeatTimer, RepeatInterval, true);
}

/*
void AEnemyAIController::UnPossess()
{
	Super::UnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AEnemyAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	if (CurrentPawn == nullptr) UE_LOG(LogTemp, Warning, TEXT("Current Pawn = nullptr"));

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem) return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0F, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		UE_LOG(LogTemp, Warning, TEXT("Next Location: %s"), *NextLocation.Location.ToString());
	}
}
*/
