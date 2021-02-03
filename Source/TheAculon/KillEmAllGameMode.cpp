// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "Aculon.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Current Score: Enemies: %d Score: %d DoorScore: %d"), EnemiesKilled, ScoreForEnemies, DoorScore);
    }
}

void AKillEmAllGameMode::IncrementScore(int32* KilledAmmount, int32* ScoreAmount, int32* AmountToDoor)
{
    Super::IncrementScore(KilledAmmount, ScoreAmount, AmountToDoor);
    EnemiesKilled += *KilledAmmount;
    ScoreForEnemies += *ScoreAmount;
    DoorScore += *AmountToDoor;
}
