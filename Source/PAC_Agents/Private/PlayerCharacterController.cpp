// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"

#include "Blueprint/UserWidget.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	if(HudWidgetClass)
	{
		HudWidget = CreateWidget(this, HudWidgetClass);
		HudWidget->AddToViewport(0);
	}
}

void APlayerCharacterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	if(HudWidget)
	{
		HudWidget->RemoveFromViewport();
	}
	if (bIsWinner)
	{
		if (WinWidgetClass)
		{
			UUserWidget* Widget = CreateWidget(this, WinWidgetClass);
			Widget->AddToViewport(0);
		}
	}
	else
	{
		if (GameOverWidgetClass && !bIsWinner)
		{
			UUserWidget* Widget = CreateWidget(this, GameOverWidgetClass);
			Widget->AddToViewport(0);
		}
	}
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}
