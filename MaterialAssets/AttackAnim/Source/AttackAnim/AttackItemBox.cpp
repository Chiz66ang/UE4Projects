// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackItemBox.h"
#include "AttackWeapon.h"
#include "AttackAnimCharacter.h"

// Sets default values
AAttackItemBox::AAttackItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);
	Effect->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(50.0F, 52.0F, 50.0F));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Box(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	if (SM_Box.Succeeded())
	{
		Box->SetStaticMesh(SM_Box.Object);
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_CHESTOPEN(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if (P_CHESTOPEN.Succeeded())
	{
		Effect->SetTemplate(P_CHESTOPEN.Object);
		Effect->bAutoActivate = false;
	}

	Box->SetRelativeLocation(FVector(0.0F, -3.5F, -30.0F));
	
	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	WeaponItemClass = AAttackWeapon::StaticClass();
}

// Called when the game starts or when spawned
void AAttackItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAttackItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAttackItemBox::OnCharacterOverlap);
}

// Called every frame
void AAttackItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackItemBox::OnCharacterOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("CharacterOverlap"));

	auto AttackAnimCharacter = Cast<AAttackAnimCharacter>(OtherActor);

	if (nullptr != AttackAnimCharacter && nullptr != WeaponItemClass)
	{
		if (AttackAnimCharacter->CanSetWeapon())
		{
			auto NewWeapon = GetWorld()->SpawnActor<AAttackWeapon>(WeaponItemClass, FVector::ZeroVector, FRotator::ZeroRotator);
			AttackAnimCharacter->SetWeapon(NewWeapon);
			Effect->Activate(true);
			Box->SetHiddenInGame(true, true);
			SetActorEnableCollision(false);
			Effect->OnSystemFinished.AddDynamic(this, &AAttackItemBox::OnEffectFinished);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s can't equip weapon currently"), *AttackAnimCharacter->GetName());
		}
	}
}

void AAttackItemBox::OnEffectFinished(UParticleSystemComponent * PSystem)
{
	Destroy();
}

