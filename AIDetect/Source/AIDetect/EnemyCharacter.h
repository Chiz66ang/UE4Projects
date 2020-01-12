// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIDetect.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FMoveToPlayerDelegate)
DECLARE_MULTICAST_DELEGATE(FPlayerFound)

UCLASS()
class AIDETECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	FMoveToPlayerDelegate MoveToPlayer;
	FPlayerFound PlayerFound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector Location;
	bool bSeePlayer;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool IsTeamLeader;

	
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
	UFUNCTION()
		void OnHearPlayer(APawn* PawnInstigator, const FVector& Location, float Volume);

		bool GetbSeePlayer()
	{
		return bSeePlayer;
	}

	void SetbSeePlayer(bool b);

	FVector ReturnLocation()
	{
		return Location;
	}

	
};
