// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "EnemyAnimInst.h"
#include "EnemyAIController.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_BODY(TEXT("/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_BODY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_BODY.Object);
	}

	FName WeaponSocket(TEXT("right_hand_S"));
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4"));
		if (SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}
	
	Alpha = 0;
	hitcount = 0;
	ishit = false;
	isAttack = false;

	AIControllerClass = AEnemyAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	UE_LOG(LogTemp, Warning, TEXT("AIController Connected"));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0F, 30.0F, 0.0F);
	GetCharacterMovement()->MaxWalkSpeed = 190.0F;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	DynamicMatInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnCharacterOverlap);
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

void AEnemyCharacter::Attack()
{
	isAttack = true;	
}

void AEnemyCharacter::Attack_End()
{
	UE_LOG(LogTemp, Warning, TEXT("AttackEnd run"));
	isAttack = false;
	OnAttackEnd.Broadcast();
}


void AEnemyCharacter::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Hit"));
	OtherActor->Destroy();

	EnemyInst = Cast<UEnemyAnimInst>(GetMesh()->GetAnimInstance());
	EnemyInst->EnemyHit();
	hitcount = EnemyInst->GetHitCount();

	if (hitcount == 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyDead"));
		SetActorEnableCollision(false);
	}
	
	FLinearColor ExColor = FLinearColor::LerpUsingHSV(FLinearColor(1.0F, 1.0F, 1.0F), FLinearColor(1.0F, 0.0F, 0.0F), Alpha);
	DynamicMatInstance->SetVectorParameterValue(FName("BodyColor"), ExColor);
	Alpha += 0.2F;
}



