// Fill out your copyright notice in the Description page of Project Settings.


#include "PACharacter.h"

#include "PAGun.h"
#include "PAPortalControlGameMode.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APACharacter::APACharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationRate = 10.0f;
	MaxHealth = 100;
}

// Called when the game starts or when spawned
void APACharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GunClass)
	{
		EquipedGun = GetWorld()->SpawnActor<APAGun>(GunClass);		
		EquipedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		                              TEXT("WeaponSocket"));
		EquipedGun->SetOwner(this);
	}

	Health = MaxHealth;
}

// Called every frame
void APACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APACharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APACharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APACharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APACharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PullTrigger"), IE_Pressed, this, &APACharacter::Shoot);
}

float APACharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	float DamageToApply = FMath::Min(Health, DamageAmount);
	Health -= DamageToApply;
	Super::TakeDamage(DamageToApply, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("auch %f"), Health)

	if (IsDead())
	{
		APAPortalControlGameMode* GameMode = GetWorld()->GetAuthGameMode<APAPortalControlGameMode>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageToApply;
}

bool APACharacter::IsDead() const
{
	return Health <= 0;
}

void APACharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}

void APACharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);
}

void APACharacter::LookUpRate(float Val)
{
	AddControllerPitchInput(Val * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void APACharacter::LookRightRate(float Val)
{
	AddControllerYawInput(Val * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void APACharacter::Shoot()
{
	if (EquipedGun)
	{
		EquipedGun->PullTrigger();
	}
}

float APACharacter::GetHealthPercentage() const
{
	return Health / MaxHealth;
}
