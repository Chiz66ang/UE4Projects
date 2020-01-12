// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacterStatComponent.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UMyCharacterStatComponent::UMyCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
	// ...
}


// Called when the game starts
void UMyCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


// Called every frame
void UMyCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CurrentStatData = MyGameInstance->GetABCharacterData(NewLevel);
	if (nullptr != CurrentStatData)
	{
		Level = NewLevel;
		//SetHP(CurrentStatData->MaxHP); 
		CurrentHP = CurrentStatData->MaxHP;
		UE_LOG(LogTemp, Warning, TEXT("MaxHP and Level Set"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Level (%d) data doesn't exist"), NewLevel);
	}
}

void UMyCharacterStatComponent::SetDamage(float NewDamage)
{
	CurrentHP -= NewDamage;
	
	/*
	if (CurrentHP <= 0.0F)
	{
		OnHPIsZero.Broadcast();
	}
	*/
}

void UMyCharacterStatComponent::SetHP(float NewDamage)
{
	CurrentHP = CurrentHP - NewDamage;
	OnHPChanged.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("HPChanged Broadcast"));
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		CurrentHP = 0.0F;
		OnHPIsZero.Broadcast();
	}
}

float UMyCharacterStatComponent::GetAttack()
{
	return CurrentStatData->Attack;
}

float UMyCharacterStatComponent::GetHPRatio()
{
	UE_LOG(LogTemp, Warning, TEXT("GetHPRatio"));
	return (CurrentStatData->MaxHP < KINDA_SMALL_NUMBER) ? 0.0F: (CurrentHP/CurrentStatData->MaxHP);
}


