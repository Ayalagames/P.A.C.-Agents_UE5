// Fill out your copyright notice in the Description page of Project Settings.


#include "PABTTask_Shoot.h"

#include "AIController.h"
#include "PACharacter.h"

UPABTTask_Shoot::UPABTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UPABTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	APACharacter* ControlledPawn = Cast<APACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ControlledPawn->Shoot();
	return EBTNodeResult::Succeeded;
}