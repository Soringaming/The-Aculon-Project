// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AculonPlayerController.generated.h"

/**
 *
 */
UCLASS()
class THEACULON_API AAculonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5;

	UUserWidget* HUD;

	FTimerHandle RestartTimer;

	void SetUpHUD();
	void RemoveHUD();
};
