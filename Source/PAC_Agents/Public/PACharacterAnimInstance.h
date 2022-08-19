// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PACharacterAnimInstance.generated.h"

class APACharacter;

/**
 * 
 */
UCLASS()
class PAC_AGENTS_API UPACharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Character")
	APACharacter* OwningCharacter;

	UPROPERTY(BlueprintReadOnly, Category="Character")
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category="Character")
	float Angle;

	UPROPERTY(BlueprintReadOnly, Category="Character")
	float Pitch;

	UPROPERTY(BlueprintReadOnly, Category="Character")
	bool bIsDead;

	UPROPERTY(BlueprintReadOnly, Category="Character")
	bool bIsAirborne;
};
