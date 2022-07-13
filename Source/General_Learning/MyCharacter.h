// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#include "Blueprint/UserWidget.h"

#include "MyCharacter.generated.h"

UCLASS()
class GENERAL_LEARNING_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Current_Energy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Energy_Drain;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Max_Energy;

	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* HitComp, 
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Player_Energy_Widget_Class;
	UUserWidget* Player_Energy_Widget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* FollowCamera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	void RestartGame();

	bool bDead;

private:
	void ChangeEnergy(float amount);
};
