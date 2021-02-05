// Fill out your copyright notice in the Description page of Project Settings.


#include "AculonCheckpoint.h"
#include "Kismet/GameplayStatics.h"
#include "Aculon.h"

AAculonCheckpoint::AAculonCheckpoint()
{
    OnActorBeginOverlap.AddDynamic(this, &AAculonCheckpoint::OnOverlapBegin);
}

void AAculonCheckpoint::BeginPlay()
{
    Super::BeginPlay();
}

void AAculonCheckpoint::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == OtherActor && (OtherActor != this))
    {
        AAculon* Aculon = Cast<AAculon>(PlayerPawn);
        if (Aculon)
        {
            Aculon->SetAculonRespawnState(false);
            Aculon->SaveGame();
        }
        UE_LOG(LogTemp, Warning, TEXT("Player has entered checkpoint area"));
    }
}