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
	virtual void IncrementScore(int32* KilledAmmount, int32* ScoreAmount, int32* AmountToDoor, bool bIsSetting);

	virtual int32 GetKilled();
	virtual int32 GetScore();
	virtual int32 GetDoorScore();

};
