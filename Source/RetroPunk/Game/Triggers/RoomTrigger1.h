// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "../Camera/LevelExtraCamera.h"
#include "../../Player/Characters/TestCharacter.h"
#include "../Actors/RoomDoor.h"
#include "RoomTrigger1.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API ARoomTrigger1 : public ATriggerBox
{
	GENERATED_BODY()


public:

	ARoomTrigger1();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=LevelCamera)
		ALevelExtraCamera* CurrentCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelCamera)
		ALevelExtraCamera* PreviousCamera = nullptr;



	ARoomDoor* DoorInstance;


	ATestCharacter* PlayerCharacter;
};
