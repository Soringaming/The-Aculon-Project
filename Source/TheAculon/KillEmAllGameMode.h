// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheAculonGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 *
 */
UCLASS()
class THEACULON_API AKillEmAllGameMode : public ATheAculonGameModeBase
{
	GENERATED_BODY()

public:
	void PawnKilled(APawn* PawnKilled) override;
	void IncrementScore(int32* KilledAmmount, int32* ScoreAmount, int32* AmountToDoor) override;

	int32 GetEnemiesKilled() override;
	int32 GetScore() override;
	int32 GetDoorScore() override;

	void SetEnemiesKilled(int32* SetKilledAmount) override;
	void SetScore(int32* SetScoreAmount) override;
	void SetDoorScore(int32* SetDoorScoreAmount) override;

private:
	int32 EnemiesKilled = 0;
	int32 ScoreForEnemies = 0;
	int32 DoorScore = 0;

	void EndGame(bool bIsPlayerWinner);

};
