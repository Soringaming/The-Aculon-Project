// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Aculon.h"
#include "Kismet/GameplayStatics.h"
#include "AculonCheckpoint.generated.h"

/**
 *
 */
UCLASS()
class THEACULON_API AAculonCheckpoint : public ATriggerBox
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AAculonCheckpoint();

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);



};
