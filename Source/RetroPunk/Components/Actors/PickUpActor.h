// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/DecalComponent.h"
#include "PowerUpActor.h"
#include "PickUpActor.generated.h"

UCLASS()
class RETROPUNK_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=PowerUp)
	USphereComponent* SphereComponent= nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		UDecalComponent* DecalComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		float CooldownDuration = 5.0f;

	FTimerHandle Respawn_TimerHandle;

	UFUNCTION(BlueprintCallable,Category=PowerUp)
	void Respawn();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
	TSubclassOf<APowerUpActor> BP_PowerUpActor;

	APowerUpActor* PowerUpIntance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
