// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AEnemyAIController::AEnemyAIController()
{
	RepeatInterval = 3.0F;
}

void AEnemyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(RepeatTimerHandle, this, &AEnemyAIController::OnRepeatTimer, RepeatInterval, true);
}

void AEnemyAIController::UnPossess()
{
	Super::UnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AEnemyAIController::OnRepeatTimer()
{
	
	auto CurrentPawn = GetPawn();
	if(CurrentPawn == nullptr) UE_LOG(LogTemp, Warning, TEXT("Current Pawn = nullptr"));

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (nullptr == NavSystem) return;

	FNavLocation NextLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0F, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		UE_LOG(LogTemp, Warning, TEXT("Next Location: %s"), *NextLocation.Location.ToString());
	}
	
}
