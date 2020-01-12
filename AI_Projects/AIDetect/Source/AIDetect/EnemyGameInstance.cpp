// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyGameInstance.h"
#include "EnemyCharacter.h"

UEnemyGameInstance::UEnemyGameInstance()
{
	FoundPlayer = false;
}

void UEnemyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init Running"));
	int32 Actornumber = GetWorld()->GetActorCount();
	UE_LOG(LogTemp, Warning, TEXT("%d"), Actornumber);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyChar, EnemyArry);
	
	for (int i = 0; i < EnemyArry.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(EnemyArry[i]->GetFName().ToString()));
	}
	/*auto Enemy = Cast<AEnemyCharacter>();
	if (Enemy == nullptr) UE_LOG(LogTemp, Warning, TEXT("Enemy is null"));
	Enemy->PlayerFound.AddUObject(this, &UEnemyGameInstance::SeePlayer);*/

}

void UEnemyGameInstance::SetFoundPlayer(bool SeePlayer)
{
	FoundPlayer = SeePlayer;
}

void UEnemyGameInstance::SeePlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("See Player broadcast good"));
}
