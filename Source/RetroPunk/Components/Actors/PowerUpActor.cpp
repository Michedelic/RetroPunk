// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APowerUpActor::APowerUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCharacter = Cast<ATestCharacter>(UGameplayStatics::GetPlayerCharacter(this,0));


	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");

	PrefabMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object mesh"));
	PrefabMesh->SetupAttachment(RootComponent);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->SetupAttachment(PrefabMesh);

}


// Called when the game starts or when spawned
void APowerUpActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APowerUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("CURRENT SPEED: %f"), PlayerCharacter->GetCharacterMovement()->GetMaxSpeed());

}

#pragma region Funciones para aplicar logica del PowerUp

void APowerUpActor::OnTickPowerUp()
{
	TicksProcessed++;

	OnPowerUpTicked();

	if (TicksProcessed >= TotalNrOfTicks)
	{

		//OnExpired();

		ExpirePowerUp();

		//ELIMINAR TIEMPO
		GetWorldTimerManager().ClearTimer(PowerUpTick_TimeHandle);
	}
}

void APowerUpActor::ActivatePowerUp()
{
	
	//OnActivated();

	//this->Destroy();

	PowerUpActivated();
	
	
	if (PowerUpInterval > 0.0f)
	{
		GetWorldTimerManager().SetTimer(PowerUpTick_TimeHandle,this,&APowerUpActor::OnTickPowerUp,PowerUpInterval,false);
	}
	else {
		OnTickPowerUp();
	}

	
}

void APowerUpActor::PowerUpActivated()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed *= 2;

	//this->Destroy();

	PrefabMesh->SetVisibility(false,true);
	
}

void APowerUpActor::ExpirePowerUp()
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed /= 2;


	
}

#pragma endregion
