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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Shoot();

	UPROPERTY(EditAnywhere)
		float RotationRate = 50;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AAculonBlaster> BlasterClass;

	UPROPERTY()
		AAculonBlaster* Blaster;
};
