// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PABTService_PlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API UPABTService_PlayerLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UPABTService_PlayerLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
