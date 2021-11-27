// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "TimerManager.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(75.0f);
	RootComponent = SphereComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	DecalComponent->SetupAttachment(SphereComponent);
	DecalComponent->SetRelativeRotation(FRotator(90.0f,0.0f,0.0f));
	DecalComponent->DecalSize = FVector(75,65,65);

}


// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();

	Respawn();
	
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void APickUpActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (PowerUpIntance)
	{
		PowerUpIntance->ActivatePowerUp();

		PowerUpIntance = nullptr;

		//Colocar el tiempo para respawnear el powerup
		GetWorldTimerManager().SetTimer(Respawn_TimerHandle,this,&APickUpActor::Respawn,CooldownDuration);




	}

}

void APickUpActor::Respawn()
{
	if (BP_PowerUpActor)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PowerUpIntance = GetWorld()->SpawnActor<APowerUpActor>(BP_PowerUpActor, GetTransform(), SpawnParams);
	}
}