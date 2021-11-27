// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "DrawDebugHelpers.h"
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

		

		FHitResult Hit;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		//Particle Target
		//FVector TracerEndPoint = TraceEnd;


		if (GetWorld()->LineTraceSingleByChannel(Hit,MuzzleLocation,TraceEnd, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();

			UGameplayStatics::ApplyDamage(HitActor,Damage,MyOwner->GetInstigatorController(),this,DamageType);

		}

		DrawDebugLine(GetWorld(),MuzzleLocation,TraceEnd,FColor::Orange,false,1.0f,0,3.0f);

		UE_LOG(LogTemp, Warning, TEXT("DISPARANDO SIN RAYO DSDE WEAPON :)"));
	}


}


#pragma endregion


