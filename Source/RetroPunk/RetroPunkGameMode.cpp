// Copyright Epic Games, Inc. All Rights Reserved.

#include "RetroPunkGameMode.h"
#include "RetroPunkPlayerController.h"
#include "RetroPunkCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARetroPunkGameMode::ARetroPunkGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARetroPunkPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}