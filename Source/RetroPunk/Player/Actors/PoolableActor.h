// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoolableActor.generated.h"

UCLASS()
class RETROPUNK_API APoolableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoolableActor();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		float LifeSpan = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		bool bActive = false;

	FTimerHandle PoolableActor_TimerHandle;


	void Deactive();

	void SetActive(bool InActive);

	bool IsActive();

	//Velocidad and Direccion para el modo de particulas

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		float Velocity = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		FVector Direction = FVector::ZeroVector;

	void SetVelocity(float InVelocity);

	void SetDirection(FVector InDirection);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetLifeSpan(float InLifespan) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	friend class ATestCharacter;

};
