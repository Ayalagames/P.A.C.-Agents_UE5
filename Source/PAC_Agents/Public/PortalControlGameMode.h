// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortalControlGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API APortalControlGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);


private:
	void EndGame(bool bIsPlayerWinner);
};
