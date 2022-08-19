// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacterAnimInstance.h"

#include "PACharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UPACharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningCharacter = Cast<APACharacter>(TryGetPawnOwner());
}

void UPACharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OwningCharacter == nullptr)
	{
		OwningCharacter = Cast<APACharacter>(TryGetPawnOwner());
	}

	if (OwningCharacter == nullptr)
	{
		return;
	}

	bIsDead = OwningCharacter->IsDead();
	bIsAirborne = OwningCharacter->GetCharacterMovement()->IsFalling();

	Speed = OwningCharacter->GetVelocity().Length();
	FVector LocalDirection = UKismetMathLibrary::InverseTransformDirection(
		OwningCharacter->GetTransform(), OwningCharacter->GetVelocity());
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(LocalDirection);
	Angle = MovementRotation.Yaw;
	Pitch = UKismetMathLibrary::NormalizedDeltaRotator(OwningCharacter->GetControlRotation(),
	                                                   OwningCharacter->GetActorRotation()).Pitch;
}
