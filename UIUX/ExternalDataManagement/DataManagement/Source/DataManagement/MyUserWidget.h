// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DataManagement.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DATAMANAGEMENT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharacterStat(class UMyCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UMyCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
		class UProgressBar* HPProgressBar;
	
};
