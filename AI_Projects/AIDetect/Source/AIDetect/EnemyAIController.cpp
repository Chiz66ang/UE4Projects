// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

const FName AEnemyAIController::TargetPosKey(TEXT("TargetPos"));
const FName AEnemyAIController::HidePosKey(TEXT("HidePos"));
const FName AEnemyAIController::bHearGunKey(TEXT("HearGun"));
const FName AEnemyAIController::LookPosKey(TEXT("LookPos"));
const FName AEnemyAIController::TeamLeaderKey(TEXT("TeamLeader"));

AEnemyAIController::AEnemyAIController()
{
	//RepeatInterval = 0.5F;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/AI/BBAsset.BBAsset"));
	if (BBObject.Succeeded())
	{
		BBAsset = BBObject.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/AI/BTAsset.BTAsset"));
	if (BTObject.Succeeded())
	{
		BTAsset = BTObject.Object;
	}
}

void AEnemyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	UseBlackboard(BBAsset, Blackboard);
	RunBehaviorTree(BTAsset);
	//GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AEnemyAIController::OnRepeatTimer, RepeatInterval, true);
}

void AEnemyAIController::UnPossess()
{
	Super::UnPossess();
	//GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AEnemyAIController::MoveToTarget(FVector Location)
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(TargetPosKey, Location);
	}
}

void AEnemyAIController::HearGunSound(bool heargun)
{

	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsBool(bHearGunKey, heargun);
		//UE_LOG(LogTemp, Warning, TEXT("heargun: %s"), heargun);
	}
	else UE_LOG(LogTemp, Warning, TEXT("no"));
}

void AEnemyAIController::HearFootSound(FVector Location)
{
	if (UseBlackboard(BBAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(LookPosKey, Location);
	}
}

//void AEnemyAIController::OnRepeatTimer()
//{
//
//	Enemy = Cast<AEnemyCharacter>(GetPawn());
//	Enemy->MoveToPlayer.AddLambda([this]()->void {
//		UE_LOG(LogTemp, Warning, TEXT("MoveToDelegate active"));
//
//		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Enemy->ReturnLocation());
//
//	});
//	
//	if (!Enemy->GetbSeePlayer())
//	{
//
//		auto CurrentPawn = GetPawn();
//		if (CurrentPawn == nullptr) UE_LOG(LogTemp, Warning, TEXT("Current Pawn = nullptr"));
//
//		UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//		if (nullptr == NavSystem) return;
//	
//		FNavLocation NextLocation;
//		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0F, NextLocation))
//		{
//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
//			UE_LOG(LogTemp, Warning, TEXT("Next Location: %s"), *NextLocation.Location.ToString());
//		}
//	}
//	Enemy->SetbSeePlayer(false);
//}
