// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootProject.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInst.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTPROJECT_API UEnemyAnimInst : public UAnimInstance
{
	GENERATED_BODY()

public:
	UEnemyAnimInst();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void EnemyHit();
	void EnemyAttack();

	int GetHitCount();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float PawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hit, Meta = (AllowPrivateAccess = true))
		bool isHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Hit, Meta = (AllowPrivateAccess = true))
		int HitCount;
	
};
