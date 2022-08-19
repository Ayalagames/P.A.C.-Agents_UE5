// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API APAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HudWidgetClass;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5;

	UPROPERTY()
	UUserWidget* HudWidget;
};
