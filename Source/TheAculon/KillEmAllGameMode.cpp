// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "Aculon.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Current Score: Enemies: %d Score: %d DoorScore: %d"), EnemiesKilled, ScoreForEnemies, DoorScore);
    }

    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AKillEmAllGameMode::IncrementScore(int32* KilledAmmount, int32* ScoreAmount, int32* AmountToDoor, bool bIsSetting)
{
    Super::IncrementScore(KilledAmmount, ScoreAmount, AmountToDoor, bIsSetting);
    if (bIsSetting)
    {
        EnemiesKilled = *KilledAmmount;
        ScoreForEnemies = *ScoreAmount;
        DoorScore = *AmountToDoor;
    }
    else
    {
        EnemiesKilled += *KilledAmmount;
        ScoreForEnemies += *ScoreAmount;
        DoorScore += *AmountToDoor;
    }
}

int32 AKillEmAllGameMode::GetKilled()
{
    return EnemiesKilled;
}

int32 AKillEmAllGameMode::GetScore()
{
    return ScoreForEnemies;
}

int32 AKillEmAllGameMode::GetDoorScore()
{
    return DoorScore;
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
