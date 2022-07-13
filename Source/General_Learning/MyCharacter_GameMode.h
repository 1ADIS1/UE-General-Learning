// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyCharacter_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GENERAL_LEARNING_API AMyCharacter_GameMode : public AGameMode
{
	GENERATED_BODY()


	AMyCharacter_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> Object_To_Spawn;

	float Spawn_Z = 4500.f;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	void SpawnCooldown();
};
