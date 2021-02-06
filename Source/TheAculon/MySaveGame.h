// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class THEACULON_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UMySaveGame();

	UPROPERTY(EditAnywhere)
		FVector PlayerLocation;

	UPROPERTY(EditAnywhere)
		FRotator PlayerRotation;

	UPROPERTY(EditAnywhere)
		int32 PlayerEnemiesKilled;

	UPROPERTY(EditAnywhere)
		int32 PlayerScore;

	UPROPERTY(EditAnywhere)
		int32 PlayerDoorScore;
	
	UPROPERTY(EditAnywhere)
		FString AculonCurrentLevelTitle;
};
