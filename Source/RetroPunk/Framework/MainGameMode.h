// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../Player/HUD/DebugHUD.h"
#include "Sound/SoundCue.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AMainGameMode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=RetroPunk)
	USoundCue* BackgroundSoundFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RetroPunk)
		USoundCue* FinishedSoundFX = nullptr;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	
	//La cantidad de tiempo que ha transcurrido desde el inicio al final del juego
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=RetroPunk,meta=(AllowPrivateAccess=true))
	float FinishedTime = 0.0f;

	//el sonido final se ejecuta?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RetroPunk, meta = (AllowPrivateAccess = true))
		bool FinishedSoundPlayed = false;
	
};
