// Fill out your copyright notice in the Description page of Project Settings.


#include "PAGun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APAGun::APAGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void APAGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APAGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APAGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

		FHitResult HitResult;
		FVector ShotDirection;
		if (GunTrace(HitResult, ShotDirection))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location,
			                                         ShotDirection.Rotation());
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);
			//DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 3);
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
				HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
			}
		}
	}
}

bool APAGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	const AController* OwnerController = GetOwnerController();

	FRotator Rot;
	FVector Pos;
	OwnerController->GetPlayerViewPoint(Pos, Rot);
	ShotDirection = -Rot.Vector();

	FVector End = Pos + Rot.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	Params.AddIgnoredActor(this);
	return GetWorld()->LineTraceSingleByChannel(Hit, Pos, End, ECC_GameTraceChannel1, Params);
}

AController* APAGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)return nullptr;

	return OwnerPawn->GetController();
}
