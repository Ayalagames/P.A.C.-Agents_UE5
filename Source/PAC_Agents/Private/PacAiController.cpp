// Fill out your copyright notice in the Description page of Project Settings.


#include "PacAiController.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void APacAiController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void APacAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool APacAiController::IsDead() const
{
	APlayerCharacter* ControlledCharacter = Cast<APlayerCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
