// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataManagement.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class DATAMANAGEMENT_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Trap)
		UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Trap)
		UStaticMeshComponent* Trap;

	UPROPERTY(VisibleAnywhere, Category = Effect)
		UParticleSystemComponent* Effect;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
