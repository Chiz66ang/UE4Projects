// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter2.h"

// Sets default values
AEnemyCharacter2::AEnemyCharacter2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EnemyDead = false;
	TotalDamage = 0.0F;
}

float AEnemyCharacter2::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	TotalDamage += FinalDamage;
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s took Damage: %f"), *GetName(), TotalDamage);

	if (TotalDamage >= 150.0F)
	{
		EnemyDead = true;
		SetActorEnableCollision(false);
	}
	return TotalDamage;
}

// Called when the game starts or when spawned
void AEnemyCharacter2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

