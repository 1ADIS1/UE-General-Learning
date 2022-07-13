// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;

	Current_Energy = 100.f;
}

void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* HitComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, 
	const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Energiser")) {
		{
			UE_LOG(LogTemp, Warning, TEXT("Energised!"));
		}

		ChangeEnergy(30.f);
		OtherActor->Destroy();
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnBeginOverlap);

	if (Player_Energy_Widget_Class != nullptr) {
		Player_Energy_Widget = CreateWidget(GetWorld(), Player_Energy_Widget_Class);
		Player_Energy_Widget->AddToViewport();
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Current_Energy -= DeltaTime * Energy_Drain;

	if (Current_Energy < 0.f) {
		if (bDead == true) return;

		bDead = true;
		// Make character a ragdoll
		GetMesh()->SetSimulatePhysics(true);

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, 
			this, 
			&AMyCharacter::RestartGame,
			3.0f, 
			false
		);
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	
	// Bind action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

}

void AMyCharacter::MoveForward(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void AMyCharacter::MoveRight(float Axis)
{
	if (!bDead) {
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void AMyCharacter::RestartGame()
{
	UGameplayStatics::OpenLevel(
		this, 
		FName(*GetWorld()->GetName()), 
		false
	);
}

void AMyCharacter::ChangeEnergy(float amount)
{
	if (amount + Current_Energy < Max_Energy) {
		Current_Energy += amount;
	}
	else {
		Current_Energy = Max_Energy;
	}

	{
		FString string = FString::Printf(TEXT("Current energy is %f"), Current_Energy);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *string)
	}
}

