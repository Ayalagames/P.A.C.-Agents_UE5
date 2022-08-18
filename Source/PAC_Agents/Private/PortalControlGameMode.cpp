// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalControlGameMode.h"

#include "EngineUtils.h"
#include "PacAiController.h"

void APortalControlGameMode::PawnKilled(APawn* PawnKilled)
{	
	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"))

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		EndGame(false);
	}

	for(APacAiController* Controller : TActorRange<APacAiController>(GetWorld()))
	{
		if(!Controller->IsDead())
		{
			return;
		}
	}
	EndGame(true);
}


void APortalControlGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
