// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "../Camera/LevelExtraCamera.h"
#include "../../Player/Characters/TestCharacter.h"
#include "RoomTriggerFinal.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API ARoomTriggerFinal : public ATriggerBox
{
	GENERATED_BODY()


public:

	ARoomTriggerFinal();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelCamera)
		ALevelExtraCamera* FinalCamera = nullptr;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelCamera)
		ALevelExtraCamera* PlayerCamera = nullptr;*/


	ATestCharacter* PlayerCharacter;
	
};
