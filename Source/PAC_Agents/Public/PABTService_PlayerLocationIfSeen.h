// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PABTService_PlayerLocationIfSeen.generated.h"

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API UPABTService_PlayerLocationIfSeen : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UPABTService_PlayerLocationIfSeen();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
