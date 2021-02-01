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
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile class to spawn
	UPROPERTY(EditAnywhere, Category = Projectile)
		TSubclassOf<class AShooterProjectile> ProjectileClass;

	// Gun muzzle offset from the camera location

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* MuzzleEffect;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* ImpactEffect;
	UPROPERTY(EditAnywhere)
		FVector ParticleScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere)
		FVector ImpactParticleScale = FVector(1, 1, 1);
	UPROPERTY(EditAnywhere)
		FRotator ParticleSpawnPointRotation = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere)
		FVector MuzzleFlashLocation = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere)
		FRotator MuzzleFlashRotation = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere)
		bool AutoDestroy = true;
	UPROPERTY(EditAnywhere)
		bool AutoActivate = true;


	UPROPERTY(EditAnywhere)
		float MaxRange = 4000;

	UPROPERTY(EditAnywhere)
		float Damage = 10;

	UPROPERTY(EditAnywhere)
		float AoeRadius = 10;
	FVector CameraLocation;
	FRotator CameraRotation;
	FVector CameraTargetLocation;
	bool IsGunCharging = false;

};
