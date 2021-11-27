// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectComponentPool.h"

// Sets default values for this component's properties
UObjectComponentPool::UObjectComponentPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UObjectComponentPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UObjectComponentPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

APoolableActor* UObjectComponentPool::GetObjectPool()
{
	if (BP_PoolableActor)
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			for (int i=0;i<PoolSize;i++)
			{
				APoolableActor* SpawnPoolableActor = World->SpawnActor<APoolableActor>(BP_PoolableActor,FVector::ZeroVector,FRotator::ZeroRotator);
				SpawnPoolableActor->SetActive(true);
				PoolArray.Emplace(SpawnPoolableActor);

				return SpawnPoolableActor;
			}
		}
	}

	for(APoolableActor* Actor : PoolArray)
	{
		if (!Actor->IsActive())
		{
			return Actor;
		}
	}

	return nullptr;
}
