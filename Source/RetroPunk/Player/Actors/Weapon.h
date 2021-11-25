// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "../PlayerControllers/CharacterPlayerController.h"
#include "Weapon.generated.h"

UCLASS()
class RETROPUNK_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const {return WeaponMesh;}


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player)
	float Damage = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TSubclassOf<UDamageType> DamageType;

	//Funcion de Disparo que va a realizar la clase arma
	UFUNCTION(BlueprintCallable,Category=Player)
	void WeaponFire();


	//Variable que contiene el nombre del socket de la arma
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player)
	FName MuzzleSocketName = "MuzzleSocket";


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	class ACharacterPlayerController* Controller = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player,meta=(AllowPrivateAccess=true))
		USkeletalMeshComponent* WeaponMesh = nullptr;
	

};
