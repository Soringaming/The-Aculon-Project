// Fill out your copyright notice in the Description page of Project Settings.


#include "Aculon.h"
#include "AculonBlaster.h"
#include "Components/CapsuleComponent.h"
#include "TheAculonGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAculon::AAculon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAculon::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Blaster = GetWorld()->SpawnActor<AAculonBlaster>(BlasterClass);
	Blaster->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Blaster->SetOwner(this);


}

bool AAculon::IsDead() const
{
	if (Health <= 0)
	{
		return true;
	}
	return false;
}

// Called every frame
void AAculon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAculon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAculon::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAculon::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AAculon::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AAculon::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AAculon::Shoot);
	PlayerInputComponent->BindAction(TEXT("Charge"), EInputEvent::IE_Pressed, this, &AAculon::StartChargingShot);
	PlayerInputComponent->BindAction(TEXT("Charge"), EInputEvent::IE_Released, this, &AAculon::StopChargingShot);
}

float AAculon::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health Left: %f"), Health);

	if (HitSound && !IsDead())
	{
		UGameplayStatics::SpawnSoundAttached(HitSound, GetMesh(), TEXT("SoundSocket"));
	}

	if (IsDead())
	{
		ATheAculonGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATheAculonGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
			if (!bHasGeneratedScore)
			{
				int32 AmmountKilled = 1;
				GameMode->IncrementScore(&AmmountKilled, &ScoreWorth, &DoorScore);
				bHasGeneratedScore = true;
			}
		}
		if (DeathSound && !bHasPlayedDeathSound)
		{
			UGameplayStatics::SpawnSoundAttached(DeathSound, GetMesh(), TEXT("SoundSocket"));
			bHasPlayedDeathSound = true;
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;

}

void AAculon::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AAculon::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AAculon::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AAculon::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AAculon::Shoot()
{
	Blaster->PullTrigger();
}

void AAculon::StartChargingShot()
{
	bIsCharging = true;
	Blaster->SetCharging(bIsCharging);
}

void AAculon::StopChargingShot()
{
	bIsCharging = false;
	Blaster->SetCharging(bIsCharging);
}

// void AAculon::LookUp(float AxisValue) 
// {
// 	AddControllerPitchInput(AxisValue);
// }

