// Fill out your copyright notice in the Description page of Project Settings.


#include "Aculon.h"
#include "AculonBlaster.h"
#include "Components/CapsuleComponent.h"
#include "TheAculonGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "AculonSaveGame.h"

// Sets default values
AAculon::AAculon()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;

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

float AAculon::GetHealthPercent() const
{
	return Health / MaxHealth;
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

	PlayerInputComponent->BindAction(TEXT("LoadGame"), EInputEvent::IE_Released, this, &AAculon::LoadGame);
	PlayerInputComponent->BindAction(TEXT("SaveGame"), EInputEvent::IE_Released, this, &AAculon::SaveGame);
}

void AAculon::SaveGame()
{
	// Create an instance of our save game class, and also the first player
	UAculonSaveGame* SaveGameInstance = Cast<UAculonSaveGame>(UGameplayStatics::CreateSaveGameObject(UAculonSaveGame::StaticClass()));
	// set the players location and rotation to be saved
	if (!bIsPlayerRespawning)
	{
		SaveGameInstance->PlayerLocation = this->GetActorLocation();
		SaveGameInstance->PlayerRotation = this->GetActorRotation();
	}

	// Get The Gamemode for saving scores
	ATheAculonGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATheAculonGameModeBase>();
	if (GameMode != nullptr)
	{
		SaveGameInstance->PlayerEnemiesKilled = GameMode->GetEnemiesKilled();
		SaveGameInstance->PlayerScore = GameMode->GetScore();
		SaveGameInstance->PlayerDoorScore = GameMode->GetDoorScore();
	}


	// save the savegameinstance
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Slot1"), 0);
}

void AAculon::LoadGame()
{
	// Create an instance of our save game class, and also the first player
	UAculonSaveGame* SaveGameInstance = Cast<UAculonSaveGame>(UGameplayStatics::CreateSaveGameObject(UAculonSaveGame::StaticClass()));
	//Load the saved game into our savegameinstance
	SaveGameInstance = Cast<UAculonSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
	ATheAculonGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATheAculonGameModeBase>();
	if (SaveGameInstance && GameMode != nullptr)
	{
		GameMode->SetEnemiesKilled(&SaveGameInstance->PlayerEnemiesKilled);
		GameMode->SetScore(&SaveGameInstance->PlayerScore);
		GameMode->SetDoorScore(&SaveGameInstance->PlayerDoorScore);
		RespawnAculon();
		this->SetActorLocation(SaveGameInstance->PlayerLocation);
		this->SetActorRotation(SaveGameInstance->PlayerRotation);
	}
}


float AAculon::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

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
		if (GetRemainingLives() <= 0 || this->GetController() != UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			DetachFromControllerPendingDestroy();
		}
		DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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

int32 AAculon::GetRemainingLives()
{
	return Lives;
}

void AAculon::RemoveLives()
{
	if (Lives > 0)
	{
		Lives -= 1;
	}
}

void AAculon::RespawnAculon()
{
	Health = MaxHealth;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ATheAculonGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATheAculonGameModeBase>();
	if (GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player score: %d Player DoorScore: %d Player Lives: %d Player Enemy Kills: %d"), GameMode->GetScore(), GameMode->GetDoorScore(), GameMode->GetEnemiesKilled());
	}
}

void AAculon::SetAculonRespawnState(bool RespawnState)
{
	bIsPlayerRespawning = RespawnState;
}


// void AAculon::LookUp(float AxisValue) 
// {
// 	AddControllerPitchInput(AxisValue);
// }

