// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackAnim.h"
#include "Animation/AnimInstance.h"
#include "AnimInst.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class ATTACKANIM_API UAnimInst : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInst();
	
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	void PlayAttackMontage(int ClickCount);
	void PlaySection(FName Name);
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	int ClickCount;
	void SetDeadAnim() { IsDead = true; }

private:
	UFUNCTION()
		void AnimNotify_AttackHitCheck();
	UFUNCTION()
		void AnimNotify_NextAttackCheck();

	UFUNCTION()
		void AnimNotify_SectionEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movespeed, Meta = (AllowPrivateAccess = true))
		float PawnSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
		UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool IsDead;
	
};
