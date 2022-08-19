// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PABTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API UPABTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPABTTask_Shoot();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
