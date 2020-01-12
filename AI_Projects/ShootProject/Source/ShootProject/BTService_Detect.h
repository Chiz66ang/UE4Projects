// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootProject.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_Detect();

protected:
	//서비스가 포함된 컴포짓 노드가 활성화 되었을 때 주기적으로 돌아가는 함수
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	//class AEnemyCharacter* AC;
};
