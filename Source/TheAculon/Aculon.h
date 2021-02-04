// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aculon.generated.h"

class AAculonBlaster;

UCLASS()
class THEACULON_API AAculon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAculon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void ChargedShot();
	void StartChargingShot();
	void StopChargingShot();

	bool bIsCharging = false;
	bool bHasGeneratedScore = false;
	bool bHasPlayedDeathSound = false;
	
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere)
		float RotationRate = 50;

	UPROPERTY(EditDefaultsOnly)
		float MaxHealth = 100;

	UPROPERTY(EditAnywhere)
		int32 ScoreWorth = 500;

	UPROPERTY(EditAnywhere)
		int32 DoorScore = 0;

	UPROPERTY(VisibleAnywhere)
		float Health;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AAculonBlaster> BlasterClass;

	UPROPERTY()
		AAculonBlaster* Blaster;
};
