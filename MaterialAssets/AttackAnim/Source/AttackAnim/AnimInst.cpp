// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInst.h"
#include "AttackAnimCharacter.h"

UAnimInst::UAnimInst()
{
	PawnSpeed = 0.0F;
	IsDead = false;
	//생성자 돌아갈 때 한번만 메모리에 적제하기 위해 static을 앞에 붙여준다. (몽타쥬 변수는 한번만 생성되어도 되기 때문)
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Action/Fight_Idle_Skeleton_Montage.Fight_Idle_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
		//UE_LOG(LogTemp, Warning, TEXT("%d"), ATTACK_MONTAGE.Object);
	}
}


void UAnimInst::PlayAttackMontage(int ClickCount)
{
	Montage_Play(AttackMontage, 1.0F);
	FString sSection = FString::Printf(TEXT("Attack%d"), ClickCount);
	Montage_JumpToSection(FName(*sSection), AttackMontage);
}

void UAnimInst::PlaySection(FName Name)
{
	Montage_Play(AttackMontage, 1.0F);
	Montage_JumpToSection(Name, AttackMontage);
}

void UAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto pawn = TryGetPawnOwner();
	if (!::IsValid(pawn)) return;
	if (::IsValid(pawn))
	{
		ACharacter* character = Cast <ACharacter>(pawn);
		PawnSpeed = character->GetCharacterMovement()->Velocity.Size();
	}
}

void UAnimInst::AnimNotify_AttackHitCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackHitCheckPoint"));
	OnAttackHitCheck.Broadcast();
}

void UAnimInst::AnimNotify_NextAttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("NextAttackCheckPoint"));
	OnNextAttackCheck.Broadcast();
}

void UAnimInst::AnimNotify_SectionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("Notify: Section Ended"));
	//OnNextAttackCheck.Broadcast();
}
