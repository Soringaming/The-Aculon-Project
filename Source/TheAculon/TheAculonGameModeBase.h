// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheAculonGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class THEACULON_API ATheAculonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	virtual void IncrementScore(int32* KilledAmmount, int32* ScoreAmount, int32* AmountToDoor);

	virtual int32 GetEnemiesKilled();
	virtual int32 GetScore();
	virtual int32 GetDoorScore();

	virtual void SetEnemiesKilled(int32* SetKilledAmount);
	virtual void SetScore(int32* SetScoreAmount);
	virtual void SetDoorScore(int32* SetDoorScoreAmount);


};
