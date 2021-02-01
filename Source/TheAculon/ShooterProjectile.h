// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterProjectile.generated.h"

UCLASS()
class THEACULON_API AShooterProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShooterProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere Collision Component
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;

	// Projectile Movement Component
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	// Function that intializes the projectile's velocity in the shoot direction
	void FireInDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
		UMaterialInstanceDynamic* ProjectileMaterialInstance;

};
