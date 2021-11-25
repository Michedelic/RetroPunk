// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}




// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::HandleTakeAnyDamage);
	}
	
	CurrentHealth = DefaultHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


#pragma region Funcion para Gestionar el dano

void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth <= 0.0f)
	{
		return;
	}

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage,0.0f,DefaultHealth);

	UE_LOG(LogTemp, Warning, TEXT("Health: %s"), *FString::SanitizeFloat(CurrentHealth));

	OnHealthChanged.Broadcast(this,CurrentHealth,Damage,DamageType,InstigatedBy,DamageCauser);

}

#pragma endregion

