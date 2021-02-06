// Fill out your copyright notice in the Description page of Project Settings.


#include "AculonPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Aculon.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"

void AAculonPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetUpHUD();
}

void AAculonPlayerController::SetUpHUD()
{
    HUD = CreateWidget(this, HUDClass);
    if (HUD)
    {
        HUD->AddToViewport();
    }
}

void AAculonPlayerController::RemoveHUD()
{
    if (HUD)
    {
        HUD->RemoveFromViewport();
    }
}

void AAculonPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AAculon* Aculon = Cast<AAculon>(PlayerPawn);

    if (Aculon == nullptr) { return; }

    // RemoveHUD();

    // if (bIsWinner)
    // {
    //     UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
    //     if (WinScreen != nullptr)
    //     {
    //         WinScreen->AddToViewport();
    //     }
    // }
    // else
    // {
    //     UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
    //     if (LoseScreen != nullptr)
    //     {
    //         LoseScreen->AddToViewport();
    //     }
    // }

    UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

    GetWorldTimerManager().SetTimer(RestartTimer, Aculon, &AAculon::LoadGame, RestartDelay);
}
