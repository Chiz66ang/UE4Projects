// Fill out your copyright notice in the Description page of Project Settings.

#include "Trap.h"
#include "DataManagementCharacter.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trap = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TRAP"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Trap->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(50.0F, 52.0F, 50.0F));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TRAP(TEXT("/Game/StarterContent/Props/SM_Bush.SM_Bush"));
	if (SM_TRAP.Succeeded())
	{
		Trap->SetStaticMesh(SM_TRAP.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_STEPPED(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (P_STEPPED.Succeeded())
	{
		Effect->SetTemplate(P_STEPPED.Object);
		Effect->bAutoActivate = false;
	}

	Trap->SetRelativeLocation(FVector(0.0F, 0.0F, -52.0F));

	//Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Trap->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrap::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ATrap::OnCharacterOverlap);
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("CharacterOverlap"));
	auto MyCharacter = Cast<ADataManagementCharacter>(OtherActor);
	if (nullptr != MyCharacter)
	{
		Effect->Activate(true);
		FDamageEvent DamageEvent;
		MyCharacter->TakeDamage(50, DamageEvent, MyCharacter->GetController(), this);
	}

}

