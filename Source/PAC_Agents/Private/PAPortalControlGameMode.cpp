// Fill out your copyright notice in the Description page of Project Settings.


#include "PAPortalControlGameMode.h"

#include "EngineUtils.h"
#include "PAAiController.h"

void APAPortalControlGameMode::PawnKilled(APawn* PawnKilled)
{	
	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"))

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(APAAiController* Controller : TActorRange<APAAiController>(GetWorld()))
	{
		if(!Controller->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}


void APAPortalControlGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
