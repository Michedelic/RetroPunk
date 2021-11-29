// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "Ball.h"
#include "BallGoal.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API ABallGoal : public ATriggerSphere
{
	GENERATED_BODY()

public:

	ABallGoal();

	//elpoder del magnetismo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Goal)
		float Magnetism = 2000.0f;

	UFUNCTION(BlueprintCallable, Category = Goal)
		bool HasBallBearing() const;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Goal)
	float MinimumDistance = 75.0f;

protected:

	//Esconder la colision y el componente sprite
	virtual void PostInitializeComponents() override;

	//Anadir al arreglo los ball que estan aproximandose al centro del aro (meta)
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//Remover al arreglo los ball que estan aproximandose al centro del aro (meta)
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	virtual void Tick(float DeltaTime) override;

private:

	//Arreglo de tipo Ball que se aproxima 
	UPROPERTY(Transient)
		TArray<ABall*> Balls;
	
};
