// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"

#include "MyCharacter_GameMode.h"

AMyCharacter_GameMode::AMyCharacter_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, 
		this,
		&AMyCharacter_GameMode::SpawnCooldown,
		FMath::RandRange(1.3f, 4.3f),
		true
	);
}

void AMyCharacter_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCharacter_GameMode::SpawnCooldown()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

	GetWorld()->SpawnActor(Object_To_Spawn, &SpawnPosition, &SpawnRotation);
}
