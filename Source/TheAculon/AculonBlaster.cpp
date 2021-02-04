// Fill out your copyright notice in the Description page of Project Settings.


#include "AculonBlaster.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AAculonBlaster::AAculonBlaster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AAculonBlaster::PullTrigger()
{
	if (MuzzleFlash)
	{
		UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"), MuzzleFlashLocation, MuzzleFlashRotation, EAttachLocation::SnapToTarget, AutoDestroy, AutoActivate);
	}
	if (MuzzleSound)
	{
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if (bSuccess)
	{
		if (ImpactEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation(), ImpactParticleScale, AutoDestroy, AutoActivate);
		}
		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		}
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			// FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			// HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			AController* OwnerController = GetOwnerController();
			UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, Hit.Location, AoeRadius, nullptr, TArray<AActor*>(), this, (AController*)GetOwner(), true, ECC_GameTraceChannel1);
		}
	}
}

void AAculonBlaster::SetCharging(bool bIsCharging)
{
	if (bIsCharging) { IsGunCharging = true; }
	else { IsGunCharging = false; }
}

// Called when the game starts or when spawned
void AAculonBlaster::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAculonBlaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MuzzleEffect && IsGunCharging)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleEffect, Mesh->GetSocketLocation("MuzzleFlashSocket"), Mesh->GetSocketRotation("MuzzleFlashSocket"), ParticleScale, AutoDestroy, AutoActivate);
		// UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleEffect, Mesh, TEXT("MuzzleFlashSocket"), MuzzleFlashLocation, MuzzleFlashRotation, EAttachLocation::SnapToTarget, AutoDestroy, AutoActivate);
	}

}

bool AAculonBlaster::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	CameraLocation = Location;
	CameraRotation = Rotation;
	CameraTargetLocation = End;
	ShotDirection = -Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AAculonBlaster::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();
}

