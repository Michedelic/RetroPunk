// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystem.h"
#include "../../Player/Components/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "BotEnemy.generated.h"

UCLASS()
class RETROPUNK_API ABotEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABotEnemy();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=AI)
	UStaticMeshComponent* BotMesh = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=AI)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		FVector NextPathPoint = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float ExplosionRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float ExplosionDamage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool bExploded = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float RequiredDistanceToTarget = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		float MovementForce = 650.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool bUseVelocityChange = true;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		UParticleSystem* ExplosionFX = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		UHealthComponent* BotHealthComponent = nullptr;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=AI)
	float CurrentBotHealth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
		bool bStartedSelfDestruction = false;


	UMaterialInstanceDynamic* MaterialInc = nullptr;


	UFUNCTION(BlueprintCallable,Category="AI")
	void HandleTakeDamage(UHealthComponent* healthComponent,float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable,Category="AI")
	void SelfDestruction();

	UFUNCTION(BlueprintCallable,Category="AI")
	FVector GetNextPathPoint();

	UFUNCTION(BlueprintCallable,Category="AI")
	void MoveBot();


	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	FTimerHandle TimerHandle_SelfDamage;

	UFUNCTION(BlueprintCallable,Category="AI")
	void DamageSelf();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
