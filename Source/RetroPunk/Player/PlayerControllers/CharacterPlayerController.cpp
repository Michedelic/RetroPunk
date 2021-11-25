// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPlayerController.h"
#include "../Characters/TestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

ACharacterPlayerController::ACharacterPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//GetMousePosition();

}

void ACharacterPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	if (ATestCharacter* character = Cast<ATestCharacter>(UGameplayStatics::GetActorOfClass(this, ATestCharacter::StaticClass())))
	{
		//if (character->bDied == true)
		//{
		//	//character->SetActorRotation(FRotator(0.0f));

		//	//SetShowMouseCursor(false);
		//	
		//}
	}
}

