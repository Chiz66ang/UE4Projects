// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootProject.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class SHOOTPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, Category = Weapon)
		USkeletalMeshComponent* Weapon;

	UMaterialInstanceDynamic* DynamicMatInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UEnemyAnimInst* EnemyInst;

	float Alpha;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	int hitcount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool ishit;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Attack)
	bool isAttack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void Attack_End();

	FOnAttackEndDelegate OnAttackEnd;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
