// Fill out your copyright notice in the Description page of Project Settings.


#include "BotEnemy.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "../../Player/Characters/TestCharacter.h"

// Sets default values
ABotEnemy::ABotEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bot Enemy Mesh"));
	BotMesh->SetCanEverAffectNavigation(false);
	BotMesh->SetSimulatePhysics(true);
	RootComponent = BotMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetSphereRadius(ExplosionRadius);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereComponent->SetupAttachment(BotMesh);


	BotHealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Bot Health"));
	BotHealthComponent->OnHealthChanged.AddDynamic(this,&ABotEnemy::HandleTakeDamage);

}


// Called when the game starts or when spawned
void ABotEnemy::BeginPlay()
{
	Super::BeginPlay();

	NextPathPoint = GetNextPathPoint();
	

	//OnActorBeginOverlap.AddDynamic(this);

}

// Called every frame
void ABotEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveBot();

}




void ABotEnemy::HandleTakeDamage(UHealthComponent* healthComponent, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentBotHealth = Health;

	if (MaterialInc == nullptr)
	{
		MaterialInc = BotMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(0, BotMesh->GetMaterial(0));
	}

	if (MaterialInc)
	{
		MaterialInc->SetScalarParameterValue(FName("LastTimeDamageTaken"),GetWorld()->TimeSeconds);
	}
	

	UE_LOG(LogTemp,Warning,TEXT("Bot Health: %s of %s"),*FString::SanitizeFloat(Health),*GetName());

	if (Health <= 0.0f)
	{
		SelfDestruction();
	}

}

void ABotEnemy::SelfDestruction()
{
	if (bExploded)
	{
		return;
	}

	bExploded  = true;

	TArray<AActor*> IgnoredActors;
	IgnoredActors.Emplace(this);

	UGameplayStatics::ApplyRadialDamage(GetWorld(),ExplosionDamage,GetActorLocation(),ExplosionRadius,nullptr,IgnoredActors,this,GetInstigatorController(),true);

	DrawDebugSphere(GetWorld(),GetActorLocation(),ExplosionRadius,12,FColor::Red,false,2.0f,0,1.0f);


	Destroy();
}

FVector ABotEnemy::GetNextPathPoint()
{	

	ACharacter* PlayerPawn = UGameplayStatics::GetPlayerCharacter(GetWorld(),0);

	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(),GetActorLocation(), PlayerPawn);

	if (NavPath->PathPoints.Num() > 1)
	{
		
		return NavPath->PathPoints[1];
	}
	
	return GetActorLocation();
}

void ABotEnemy::MoveBot()
{
	float DistanceToTarget = (NextPathPoint - GetActorLocation()).Size();

	if (DistanceToTarget <= RequiredDistanceToTarget)
	{
		NextPathPoint = GetNextPathPoint();

		DrawDebugString(GetWorld(), GetActorLocation(), "PUNTO ALCANZADO !");
	}
	else {
		//seguir moviendose al objetivo
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();

		ForceDirection *= MovementForce;

		BotMesh->AddForce(ForceDirection,NAME_None, bUseVelocityChange);

		DrawDebugDirectionalArrow(GetWorld(),GetActorLocation(),GetActorLocation() + ForceDirection,32,FColor::Blue,false,0.0f,0.0f,2.0f);

	}

	DrawDebugSphere(GetWorld(),NextPathPoint,20.0f,12,FColor::Green,false,4.0f,1.0f);
	
}

void ABotEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{

	if (!bStartedSelfDestruction)
	{
		ATestCharacter* PlayerPawn = Cast<ATestCharacter>(OtherActor);

		if (PlayerPawn)
		{
			//hicimos contacto con el jugador

			//comenzar la secuencia de auto desctruccion del enemigo bot
			GetWorldTimerManager().SetTimer(TimerHandle_SelfDamage, this, &ABotEnemy::DamageSelf, 0.5f, true, 0.0f);

			bStartedSelfDestruction = true;
		}
	}
	
}

void ABotEnemy::DamageSelf()
{
	UGameplayStatics::ApplyDamage(this,10.0f,GetInstigatorController(),this,nullptr);
}
