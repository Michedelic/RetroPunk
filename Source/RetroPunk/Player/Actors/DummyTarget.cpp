// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyTarget.h"

// Sets default values
ADummyTarget::ADummyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DummyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Dummy Mesh"));
	RootComponent = DummyMesh;


}

// Called when the game starts or when spawned
void ADummyTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

