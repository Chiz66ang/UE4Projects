// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "CppCubeActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN (MyLog, Log, All);

UCLASS()
class GRAPHICTEST_API ACppCubeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACppCubeActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = ParticleSystem)
		UParticleSystem* ParticleSystem;

	UPROPERTY(VisibleAnywhere, Category = Cube)
		UStaticMeshComponent* Cube;

	UPROPERTY(VisibleAnywhere, Category = Box)
		UBoxComponent* Box;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	float EmissiveValue;
	bool Emitting;
	bool Collide;
	UMaterialInstanceDynamic* DynamicMatInstance;
	float Alpha;
};
