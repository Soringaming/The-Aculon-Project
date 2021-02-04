// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "ShooterProjectile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AculonBlaster.generated.h"

UCLASS()
class THEACULON_API AAculonBlaster : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAculonBlaster();

	void PullTrigger();
	void SetCharging(bool bIsCharging);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn


	// Gun muzzle offset from the camera location



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
		UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "FX")
		class UNiagaraSystem* MuzzleEffect;
	UPROPERTY(EditAnywhere, Category = "FX")
		class UNiagaraSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "FX")
		class UNiagaraSystem* ImpactEffect;
	UPROPERTY(EditAnywhere, Category = "FX")
		FVector ParticleScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, Category = "FX")
		FVector ImpactParticleScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere, Category = "FX")
		FRotator ParticleSpawnPointRotation = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere, Category = "FX")
		FVector MuzzleFlashLocation = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, Category = "FX")
		FRotator MuzzleFlashRotation = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere, Category = "FX")
		bool AutoDestroy = true;
	UPROPERTY(EditAnywhere, Category = "FX")
		bool AutoActivate = true;


	UPROPERTY(EditAnywhere, Category = "Gun Traits")
		float MaxRange = 4000;

	UPROPERTY(EditAnywhere, Category = "Gun Traits")
		float Damage = 10;

	UPROPERTY(EditAnywhere, Category = "Gun Traits")
		float AoeRadius = 10;
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector CameraTargetLocation;
	bool IsGunCharging = false;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	AController* GetOwnerController() const;

};
