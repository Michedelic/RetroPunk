// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangedSignature, UHealthComponent*, healthComponent, float, Health, float, HealthDelta, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(DreamGame), meta=(BlueprintSpawnableComponent) )
class RETROPUNK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player)
	float DefaultHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float CurrentHealth = 0.0f;


	UFUNCTION(BlueprintCallable,Category=Player)
		void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	//Funcion para aumentar vida como Power Up
	UFUNCTION(BlueprintCallable,Category=PowerUp)
	void HandleHealPowerUp(float HealAmount);


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player)
	USoundCue* SoundFX = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable,Category="Events")
		FOnHealthChangedSignature OnHealthChanged;

	float GetHealth() const;
		
};
