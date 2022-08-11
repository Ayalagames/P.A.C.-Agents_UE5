// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn)
		{
			AController* OwnerController = OwnerPawn->GetController();
			if (OwnerController)
			{
				FRotator Rot;
				FVector Pos;
				OwnerController->GetPlayerViewPoint(Pos, Rot);

				FVector End = Pos + Rot.Vector() * MaxRange;
				FHitResult HitResult;
				if (GetWorld()->LineTraceSingleByChannel(HitResult, Pos, End, ECC_GameTraceChannel1))
				{
					FVector ShotDirection = -Rot.Vector();
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location,
					                                         ShotDirection.Rotation());
					DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, false, 3);
					AActor* HitActor = HitResult.GetActor();
					if (HitActor)
					{
						FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
						HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
					}
				}
			}
		}
	}
}
