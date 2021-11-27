// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolableActor.h"

// Sets default values
APoolableActor::APoolableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SetActorEnableCollision(false);
}



// Called when the game starts or when spawned
void APoolableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APoolableActor::SetLifeSpan(float InLifespan)
{
	LifeSpan = InLifespan;

	GetWorldTimerManager().SetTimer(PoolableActor_TimerHandle,this,&ThisClass::Deactive,LifeSpan,false);
}

// Called every frame
void APoolableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Velocity * Direction * DeltaTime);

}

#pragma region Funciones generales para el Pool

void APoolableActor::Deactive()
{
	SetActive(false);
}

void APoolableActor::SetActive(bool InActive)
{
	 bActive = InActive;
	 SetActorHiddenInGame(!InActive);
}

bool APoolableActor::IsActive()
{
	return bActive;
}

#pragma endregion

#pragma region Funciones para el pool modo particulas

void APoolableActor::SetVelocity(float InVelocity)
{
	Velocity = InVelocity;
}

void APoolableActor::SetDirection(FVector InDirection)
{
	Direction = InDirection;
}

#pragma endregion

