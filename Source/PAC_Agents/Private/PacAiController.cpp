// Fill out your copyright notice in the Description page of Project Settings.


#include "PacAiController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void APacAiController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void APacAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const APlayerCharacter* ControllingPawn = Cast<APlayerCharacter>(GetPawn());
	if (ControllingPawn && ControllingPawn->IsDead())
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
		return;
	}

	if (LineOfSightTo(PlayerPawn))
	{
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn, 200);
	}
	else
	{
		ClearFocus(EAIFocusPriority::Gameplay);
		StopMovement();
	}
}
