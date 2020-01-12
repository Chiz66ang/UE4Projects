// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAnimInst.h"
#include "EnemyCharacter.h"

UEnemyAnimInst::UEnemyAnimInst()
{
	PawnSpeed = 0;
	isHit = false;
	HitCount = 0;
}


void UEnemyAnimInst::NativeUpdateAnimation(float DeltaSeconds)
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

void UEnemyAnimInst::EnemyHit()
{
	isHit = true;
	++HitCount;
	UE_LOG(LogTemp, Warning, TEXT("HitCount: %d"), HitCount);
	isHit = false;
}

void UEnemyAnimInst::EnemyAttack()
{
}


int UEnemyAnimInst::GetHitCount()
{
	return HitCount;
}
