// Fill out your copyright notice in the Description page of Project Settings.


#include "AculonSaveGame.h"


UAculonSaveGame::UAculonSaveGame()
{
    PlayerLocation = FVector(0.f, 0.f, 0.f);
    PlayerRotation = FRotator(0.f, 0.f, 0.f);
    PlayerScore = 0;
    PlayerDoorScore = 0;
}
