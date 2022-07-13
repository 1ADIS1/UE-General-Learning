// Copyright Epic Games, Inc. All Rights Reserved.

#include "General_LearningGameMode.h"
#include "General_LearningCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGeneral_LearningGameMode::AGeneral_LearningGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
