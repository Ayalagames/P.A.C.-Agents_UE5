// Fill out your copyright notice in the Description page of Project Settings.


#include "PABTTask_ClearBlackboardValue.h"

#include "BehaviorTree/BlackboardComponent.h"

UPABTTask_ClearBlackboardValue::UPABTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");
}

EBTNodeResult::Type UPABTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());	
	return EBTNodeResult::Succeeded;
}