// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackAnim.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter2.generated.h"

UCLASS()
class ATTACKANIM_API AEnemyCharacter2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter2();
	float TotalDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAnimInst* AAnim;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool EnemyDead;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
