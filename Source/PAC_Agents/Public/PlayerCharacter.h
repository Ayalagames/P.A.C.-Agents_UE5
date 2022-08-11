// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PAC_AGENTS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Val);
	void MoveRight(float Val);

	void LookUpRate(float Val);
	void LookRightRate(float Val);

	void Shoot();

	UPROPERTY(EditAnywhere)
	float RotationRate;

	//UPROPERTY(EditDefaultsOnly)
	//TSubclassOf<class AGun> GunClass;

	//UPROPERTY()
	//AGun* EquipedGun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
