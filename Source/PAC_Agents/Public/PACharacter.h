// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacter.generated.h"

class APAGun;

UCLASS()
class PAC_AGENTS_API APACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	void Shoot();

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

private:
	void MoveForward(float Val);
	void MoveRight(float Val);

	void LookUpRate(float Val);
	void LookRightRate(float Val);

	UPROPERTY(EditAnywhere)
	float RotationRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APAGun> GunClass;

	UPROPERTY()
	APAGun* EquipedGun;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
