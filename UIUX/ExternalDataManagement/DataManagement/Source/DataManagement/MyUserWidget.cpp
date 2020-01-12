// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "MyCharacterStatComponent.h"
#include "Components/ProgressBar.h"

void UMyUserWidget::BindCharacterStat(UMyCharacterStatComponent* NewCharacterStat)
{
	CurrentCharacterStat = NewCharacterStat;
	NewCharacterStat->OnHPChanged.AddUObject(this, &UMyUserWidget::UpdateHPWidget);

	/*
	NewCharacterStat->OnHPChanged.AddLambda([this]()->void {
		UE_LOG(LogTemp, Warning, TEXT("Broadcast recieved"));
		if (CurrentCharacterStat.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("HPRatio: %f"), CurrentCharacterStat->GetHPRatio());
		}
	});
	*/
}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	if (HPProgressBar == nullptr) UE_LOG(LogTemp, Warning, TEXT("HPProgressBar = nullptr"));
	UpdateHPWidget();
}

void UMyUserWidget::UpdateHPWidget()
{
	if (CurrentCharacterStat.IsValid())
	{
		if (nullptr != HPProgressBar)
		{
			HPProgressBar->SetPercent(CurrentCharacterStat->GetHPRatio());
		}
	}
}
