// Fill out your copyright notice in the Description page of Project Settings.

#include "CppCubeActor.h"

DEFINE_LOG_CATEGORY(MyLog);

// Sets default values
ACppCubeActor::ACppCubeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("PARTICLESYSTEM"));
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CUBE"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	RootComponent = Cube;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACppCubeActor::OnBoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACppCubeActor::OnBoxEndOverlap);
	Box->SetupAttachment(Cube);

	EmissiveValue = 0;
	Emitting = false;
	Collide = false;
	Alpha = 0;
	
}

// Called when the game starts or when spawned
void ACppCubeActor::BeginPlay()
{
	Super::BeginPlay();
	DynamicMatInstance = Cube->CreateAndSetMaterialInstanceDynamic(0);
}

// Called every frame
void ACppCubeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Collide)
	{
		DynamicMatInstance->SetScalarParameterValue(FName("Emissive"), 0);
		FLinearColor ExColor = FLinearColor::LerpUsingHSV(FLinearColor(1.0F, 1.0F, 1.0F), FLinearColor(1.0F, 0.0F, 0.0F), Alpha);
		DynamicMatInstance->SetVectorParameterValue(FName("Custom Color"), ExColor);
		Alpha += DeltaTime * 0.5;
		if (Alpha >= 1)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation(), FRotator::ZeroRotator, true);
			AActor::Destroy();
		}
	}
	else
	{
		DeltaTime = Emitting ? DeltaTime : -DeltaTime;
		EmissiveValue += DeltaTime * 50;
		DynamicMatInstance->SetScalarParameterValue(FName("Emissive"), EmissiveValue);
		if (Emitting && EmissiveValue >= 100.0F) Emitting = false;
		else if (!Emitting && EmissiveValue <= 0.0F) Emitting = true;
	}

	/*
	if (EmissiveValue < 100.0F && Emitting == true)
	{
		EmissiveValue = (DeltaTime * 50) + EmissiveValue;
		if (EmissiveValue >= 100.0F) Emitting = false;
	}

	else if (EmissiveValue >= 100.0F && Emitting == false)
	{
		EmissiveValue = (DeltaTime * (-1) * 50) +EmissiveValue;
	}
	
	else if (EmissiveValue <= 100.0F && Emitting == false)
	{
		EmissiveValue = (DeltaTime * (-1) * 50) + EmissiveValue;
		if (EmissiveValue <= 0.0F) Emitting = true;
	}
	*/
		

	
}

void ACppCubeActor::OnBoxBeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Collide = true;
	UE_LOG(MyLog, Warning, TEXT("Begin Overlap"));
	FLinearColor color(0.0F, 1.0F, 0.0F, 1.0F);
	DynamicMatInstance->SetVectorParameterValue(FName("Custom Color"), color);
	
	
}

void ACppCubeActor::OnBoxEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(MyLog, Warning, TEXT("End Overlap"));
	FLinearColor color(1.0F, 1.0F, 1.0F, 1.0F);
	DynamicMatInstance->SetVectorParameterValue(FName("Custom Color"), color);

}

