// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Game/Pawns/BallGoal.h"
#include "TimerManager.h"

AMainGameMode::AMainGameMode()
{
	HUDClass = ADebugHUD::StaticClass();

	PlayerCharacter = Cast<ATestCharacter>(UGameplayStatics::GetActorOfClass(this, ATestCharacter::StaticClass()));
}


void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BackgroundSoundFX)
	{
		UGameplayStatics::PlaySound2D(AActor::GetWorld(),BackgroundSoundFX);
	}

}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Determinar si todos los ball estan en el centro de los goal

	int32 numGoals = 0;
	bool bFinished = true;
	TArray<AActor*> actors;


	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABallGoal::StaticClass(),actors);

	for (const AActor* goal : actors)
	{
		numGoals++;

		if ((Cast<ABallGoal>(goal))->HasBallBearing() == false)
		{
			bFinished = false;
			break;
		}
	}


	//Si todas los ball goals tienen un ball en su centro gana y se visualiza cuanto tiempo ha transcurrido
	if (numGoals == 2 && bFinished == true)
	{
		FinishedTime += DeltaTime;
	}
	else {
		FinishedTime = 0.0f;
	}

	//si todos los goals estan llenas por lo mneos un segundo, administramos el gfinal del juego
	//el delay es para evitar que los ball pasen a tyraves de los goals sin detenerse

	if (FinishedTime > 1.0f)
	{
		//play el audio de fianl de juego
		if (FinishedSoundPlayed == false)
		{
			FinishedSoundPlayed = true;

			UGameplayStatics::PlaySound2D(GetWorld(),FinishedSoundFX);
		}
	}

	//si el juego ha terminado por lo menos igual o mayor a 15 segundos, resetea el juego al inicio
	if (FinishedTime > 5.0f)
	{

		Super::RestartGame();

	}

	//RestartWhenPlayerDies(DeltaTime);

	if (PlayerCharacter->bDied)
	{
		//GetWorldTimerManager().SetTimer(RestartPlayer_TimerHandle,this,&AMainGameMode::RestartWhenPlayerDies,0.6f,true);
		FinishedTimePlayer += DeltaTime;

	}
	else {
		FinishedTimePlayer = 0.0f;
	}

	if (FinishedTimePlayer > 2.0f)
	{
		Super::RestartGame();
	}
	

}

void AMainGameMode::RestartWhenPlayerDies(float DeltaTime)
{

	if (PlayerCharacter->bDied)
	{
		//GetWorldTimerManager().SetTimer(RestartPlayer_TimerHandle,this,&AMainGameMode::RestartWhenPlayerDies,0.6f,true);
		FinishedTime += DeltaTime;

		if (FinishedTime > 0.5f)
		{
			Super::RestartGame();
		}
		
	}else{
		FinishedTime = 0.0f;
	}
	
		
	
}

