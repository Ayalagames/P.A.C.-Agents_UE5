// Fill out your copyright notice in the Description page of Project Settings.


#include "PAAiController.h"
#include "PACharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void APAAiController::BeginPlay()
{
	Super::BeginPlay();
	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void APAAiController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool APAAiController::IsDead() const
{
	APACharacter* ControlledCharacter = Cast<APACharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
