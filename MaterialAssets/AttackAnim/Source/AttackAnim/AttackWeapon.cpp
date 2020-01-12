// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackWeapon.h"

// Sets default values
AAttackWeapon::AAttackWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = Weapon;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/Action/SK_Blade_Sucker.SK_Blade_Sucker"));
	if (SK_WEAPON.Succeeded())
	{
		Weapon->SetSkeletalMesh(SK_WEAPON.Object);
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void AAttackWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

