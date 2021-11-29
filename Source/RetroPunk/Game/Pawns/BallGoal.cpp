// Fill out your copyright notice in the Description page of Project Settings.


#include "BallGoal.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"

//funcion estatica que permite obtener el ratio (razon - proporcion) en la cantidadf entre el minimo y maximo
static float GetRation(float value, float minimum, float maximum, bool clamp = true)
{
	if (value > maximum && clamp == true)
	{
		return 1.0f;
	}
	else if (value > minimum)
	{
		return (value - minimum) / (maximum - minimum);
	}
	else {
		return 0.0f;
	}
}


ABallGoal::ABallGoal()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorHiddenInGame(false);
}

void ABallGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);

	

	GetSpriteComponent()->SetHiddenInGame(true);


}

void ABallGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Anadir magnetismo a las ball proximas, arrastrarlas al centro por medio del magnestismo
	FVector OurLocation = GetActorLocation();
	float SphereRadius = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
	float CurrentMagnetism = Magnetism;

	//Iterar el Arreglo de las Ball que se aproximan (entarr al overlap) y arrastrarlas al centro
	//usar fisicas de fuerza del magnetismo y distancia del centro

	for (ABall* ball : Balls)
	{
		FVector Difference = OurLocation - ball->GetActorLocation();

		float Distance = Difference.Size();

		FVector Direction = Difference;

		Direction.Normalize();

		float Ratio = GetRation(Distance,0.0f,SphereRadius);

		FVector Force = (1.0f - Ratio) * CurrentMagnetism * Direction;

		ball->BallMesh->AddForce(Force);

	}


}


void ABallGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABall* ball = Cast<ABall>(OtherActor);

	if (ball && ball->bMagnetized == true)
	{
		Balls.AddUnique(ball);
	}

}

void ABallGoal::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ABall* ball = Cast<ABall>(OtherActor);

	if (ball && ball->bMagnetized == true)
	{
		Balls.Remove(ball);
	}
}

bool ABallGoal::HasBallBearing() const
{
	FVector Location = GetActorLocation();

	for (const ABall* ball : Balls)
	{
		FVector Difference = Location - ball->GetActorLocation();

		float Distance = Difference.Size();

		if (Distance < MinimumDistance)
		{
			return true;
		}


	}

	return false;
}

