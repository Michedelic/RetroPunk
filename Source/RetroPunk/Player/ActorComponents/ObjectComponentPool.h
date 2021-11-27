// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Actors/PoolableActor.h"
#include "ObjectComponentPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RETROPUNK_API UObjectComponentPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectComponentPool();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Pool)
	TSubclassOf<APoolableActor> BP_PoolableActor;

	//Funcion para obetener el objeto para desarollarlo en el Pooling
	APoolableActor* GetObjectPool();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		TArray<APoolableActor*> PoolArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pool)
		int PoolSize = 5;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
