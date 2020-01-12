// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Mesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AI_Anim(TEXT("/Game/Mannequin/Animations/AI_AnimBP.AI_AnimBP_C"));
	if (AI_Anim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AI_Anim.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0F, 0.0F, -88.0F), FRotator(0.0F, -90.0F, 0.0F));

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	if (PawnSensingComp)
	{
		PawnSensingComp->bOnlySensePlayers = false;
		PawnSensingComp->SensingInterval = 0.5F;
		PawnSensingComp->SetPeripheralVisionAngle(80.0F);
		PawnSensingComp->SightRadius = 3000.0F;
		PawnSensingComp->bHearNoises = true;
		PawnSensingComp->HearingThreshold = 10000.0F;
	}
	else UE_LOG(LogTemp, Warning, TEXT("PawnSensingComp == nullptr"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePlayer);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AEnemyCharacter::OnHearPlayer);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnSeePlayer(APawn * Pawn)
{
	//bSeePlayer = true;
	if(Pawn->IsPlayerControlled())
	{ 
	UE_LOG(LogTemp, Warning, TEXT("ISeeYOU"));
	auto AIController = Cast<AEnemyAIController>(GetController());
	Location = Pawn->GetActorLocation();
	AIController->MoveToTarget(Location);
	//MoveToPlayer.Broadcast();
	//PlayerFound.Broadcast();
	}
	else return;

}

void AEnemyCharacter::OnHearPlayer(APawn * PawnInstigator, const FVector & Location, float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("IHearYOU: %f"), Volume);
	//PawnInstigator->GetActorLocation();
	auto AIHear = Cast<AEnemyAIController>(GetController());
	FString Actor = PawnInstigator->GetActorLabel();

	if (Volume <= 0.5)
	{
		AIHear->HearFootSound(PawnInstigator->GetActorLocation());
	}
	
	if(Volume >= 0.8)
	{ 
		if (Actor == TEXT("BT_EnemyLeader"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Leader?"));
		}
		else AIHear->HearGunSound(true);
	}

	
	//if (PawnInstigator->GetClass()->GetName() == TEXT("BT_EnemyLeader"))
	//{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor);
	//}
	//else UE_LOG(LogTemp, Warning, TEXT("NoCallRespond"));
}

void AEnemyCharacter::SetbSeePlayer(bool b)
{
	bSeePlayer = b;
}

