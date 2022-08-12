// Fill out your copyright notice in the Description page of Project Settings.


#include "PacAiController.h"

#include "Kismet/GameplayStatics.h"

void APacAiController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn);
}

void APacAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveToActor(PlayerPawn, 200);
}
