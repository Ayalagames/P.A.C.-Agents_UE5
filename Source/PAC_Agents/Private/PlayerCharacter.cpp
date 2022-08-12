// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Gun.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RotationRate = 10.0f;
	MaxHealth = 100;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GunClass)
	{
		EquipedGun = GetWorld()->SpawnActor<AGun>(GunClass);
		//GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
		EquipedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		                              TEXT("WeaponSocket"));
		EquipedGun->SetOwner(this);
	}

	Health = MaxHealth;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APlayerCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("PullTrigger"), IE_Pressed, this, &APlayerCharacter::Shoot);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("auch %f"), Health)
	return DamageToApply;
}

bool APlayerCharacter::IsDead() const
{
	return Health <= 0;
}

void APlayerCharacter::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector() * Val);
}

void APlayerCharacter::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector() * Val);
}

void APlayerCharacter::LookUpRate(float Val)
{
	AddControllerPitchInput(Val * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacter::LookRightRate(float Val)
{
	AddControllerYawInput(Val * RotationRate * GetWorld()->DeltaTimeSeconds);
}

void APlayerCharacter::Shoot()
{
	if (EquipedGun)
	{
		EquipedGun->PullTrigger();
	}
}
