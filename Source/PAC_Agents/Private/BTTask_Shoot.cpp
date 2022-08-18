// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "PlayerCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APlayerCharacter* ControlledPawn = Cast<APlayerCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ControlledPawn->Shoot();
	return EBTNodeResult::Succeeded;
}