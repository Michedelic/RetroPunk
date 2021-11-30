// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "../../RetroPunk.h"


// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	RootComponent = WeaponMesh;

}



// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	TimeBetweenShots = 60 / FireRate;
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


#pragma region Funciones de Acciones que va realizar este actor

void AWeapon::WeaponFire()
{
	//Line Trace, linea trazada que permitira conocer informacion del disparo unavez que colisione con un enemigo,etc...

	AActor* MyOwner = GetOwner();

	Controller = Cast<ACharacterPlayerController>(UGameplayStatics::GetActorOfClass(this,ACharacterPlayerController::StaticClass()));


	if (MyOwner && Controller)
	{

		FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		FRotator MuzzleRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);


		/*Controller->GetMouseCursor();

		Controller->DeprojectMousePositionToWorld();*/

		
		//Direccion de disparo del arma
		FVector ShotDirection = MuzzleRotation.Vector();

		FVector TraceEnd = MuzzleLocation +  ( ShotDirection * 20000.0f);

		
		//Particle Target
		FVector TracerEndPoint = TraceEnd;

		FHitResult Hit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		//Particle Target
		//FVector TracerEndPoint = TraceEnd;


		if (GetWorld()->LineTraceSingleByChannel(Hit,MuzzleLocation,TraceEnd, COLLISION_WEAPON, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();

			float ActualDamage = Damage;

			//seccion para distinguir el material de fisicas para el dano
			//EPhysicalSurface Surface = UPhysicalMaterial::
			EPhysicalSurface Surface = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

			if (Surface == SURFACE_FLESHVULNERABLE)
			{
				ActualDamage *= 2;
			}


			UGameplayStatics::ApplyDamage(HitActor, ActualDamage,MyOwner->GetInstigatorController(),this,DamageType);

			//Aplicar el efecto al momento de disparar
			UParticleSystem* SelectedEffect = nullptr;

			//switch para ver en que superficie se dispara , ya sea a un enemigo u otro objeto
			switch (Surface)
			{
				case SURFACE_FLESHDEFAULT:
				case SURFACE_FLESHVULNERABLE:
				 SelectedEffect = FleshImpactEffect;
				break;

				default:
					SelectedEffect = ImpactEffect;
				break;
			}


			if (SelectedEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),SelectedEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());


			}

			//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.ImpactPoint,Hit.ImpactNormal.Rotation());


			TracerEndPoint = Hit.ImpactPoint;

			

		}


		LastTimeFired = GetWorld()->TimeSeconds;

		//agregar un efecto en el socket ,que es el muzzle en este caso
		if (MuzzleEffect)
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, WeaponMesh, MuzzleSocketName);
		}

		if (TracerEffect)
		{
			FVector ML = WeaponMesh->GetSocketLocation(MuzzleSocketName);

			UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TracerEffect, ML);

			if (TracerComponent)
			{
				TracerComponent->SetVectorParameter(TracerTargetName, TracerEndPoint);
			}

		}

		if (FireSoundFX)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), FireSoundFX);
		}

		//DrawDebugLine(GetWorld(),MuzzleLocation,TraceEnd,FColor::Orange,false,1.0f,0,3.0f);

		//UE_LOG(LogTemp, Warning, TEXT("DISPARANDO SIN RAYO DSDE WEAPON :)"));
	}


}


#pragma endregion


void AWeapon::StartFire()
{
	float FirstDelay = FMath::Max(LastTimeFired + TimeBetweenShots - GetWorld()->TimeSeconds,0.0f);

	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShots,this,&AWeapon::WeaponFire,TimeBetweenShots,true,FirstDelay);
}

void AWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShots);
}