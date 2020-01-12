// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/GameData/ABCharacterData.ABCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
	
	if (DT_ABCHARACTER.Succeeded())
	{
		ABCharacterTable = DT_ABCHARACTER.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	//UE_LOG(LogTemp, Warning, TEXT("DropExp of Level 20 ABCharacter: %d"), GetABCharacterData(20)->DropExp);
}

FABCharacterData * UMyGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
}
