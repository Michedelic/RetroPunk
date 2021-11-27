// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Player/Characters/TestCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "PowerUpActor.generated.h"

UCLASS()
class RETROPUNK_API APowerUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpActor();

	ATestCharacter* PlayerCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=PowerUp)
	UStaticMeshComponent* PrefabMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		UPointLightComponent* PointLight = nullptr;

	//tiempo entre la ejecucion del powerup
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=PowerUp)
	float PowerUpInterval = 10.0f;


	//numero de veces que aplicamos a un powerup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		int32 TotalNrOfTicks = 0;

	//numero deticks aplicados
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		int32 TicksProcessed = 0;

	FTimerHandle TimerHandle_PowerupTick;

	UFUNCTION(BlueprintCallable,Category=PowerUp)
	void OnTickPowerUp();

	UFUNCTION(BlueprintCallable, Category = PowerUp)
		void ActivatePowerUp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		float CurrentSpeed = 0.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PowerUp)
		float HealingAmount = 20.0f;

	void PowerUpActivated();

	void ExpirePowerUp();


	void FPowerUpTicked();


	//funciones (eventos) donde la logica debe implementarse 100% en Blueprints
	UFUNCTION(BlueprintImplementableEvent,Category=PowerUp)
	void OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = PowerUp)
		void OnExpired();

	UFUNCTION(BlueprintImplementableEvent, Category = PowerUp)
		void OnPowerUpTicked();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
