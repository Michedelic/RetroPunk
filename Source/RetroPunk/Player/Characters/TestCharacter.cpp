// Fill out your copyright notice in the Description page of Project Settings.


#include "TestCharacter.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "../../RetroPunk.h"
#include "DrawDebugHelpers.h"
#include "../Actors/PoolableActor.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATestCharacter::ATestCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoomCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	BoomCamera->SetupAttachment(RootComponent);
	BoomCamera->SetUsingAbsoluteRotation(true);
	BoomCamera->bDoCollisionTest = false;
	BoomCamera->TargetArmLength = 800.0f;
	BoomCamera->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(BoomCamera, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Mejorando el movimiento del jugador
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//GetMesh()->SetSimulatePhysics(true);

	//GetCharacterMovement()->Collisi
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));


	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


	ComponentPool = CreateDefaultSubobject<UObjectComponentPool>(TEXT("Poolable Actor Component"));
}



// Called when the game starts or when spawned
void ATestCharacter::BeginPlay()
{
	Super::BeginPlay();


	//Aqui se manda a llamar la funcionpara spawnear el arma en el brazo del player cuando inicie el juego
	SpawnWeapon();

	HealthComponent->OnHealthChanged.AddDynamic(this,&ATestCharacter::OnHealthChangedComponent);

	PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

//Funcion para declarar los Inputs de los controlesy WASD, se puede modificar desde lainterfaz de UE pero quize experimentar XD
#pragma region Funcion para generar los Inputs

static void InitializeInputs()
{
	bool bindingAdded = false;

	if (bindingAdded == false)
	{
		bindingAdded = true;


		//Estableciendo Entradas del teclado
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveForward"), EKeys::W, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveForward"), EKeys::S, -1.0f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveForward"), EKeys::Gamepad_LeftY, 1.0f));

		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveRight"), EKeys::D, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveRight"), EKeys::A, -1.0f));
		//UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(FName("MoveRight"), EKeys::Gamepad_RightX, 1.0f));


		//Generarndo Inputs para Acciones (Disparos,Salto,etc...)
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(FName("Fire"),EKeys::LeftMouseButton));
		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(FName("Dash"), EKeys::SpaceBar));
		//UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping(FName("")));
	}
}

#pragma endregion



// Called every frame
void ATestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (DashTimer > 0.0f)
	//{
	//	DashTimer = FMath::Max(0.0f,DashTimer - DeltaTime);
	//}

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		/*PlayerControllerRef->Cursor*/
		//PlayerControllerRef->SetMouseLocation(-35.0f,17.0f);

		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint + FVector(-35.0f,17.0f,0.0f),20.0f,12,FColor::Red,false,-1.0f);


		RotateCharacter(HitResult.ImpactPoint + FVector(-35.0f, 17.0f, 0.0f));
	}

}

// Called to bind functionality to input
void ATestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent != nullptr);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InitializeInputs();

	//Entradas para Movimiento
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ATestCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ATestCharacter::MoveRight);

	//Entradas para Acciones (Disparos,etc...)
	PlayerInputComponent->BindAction(FName("Fire"),EInputEvent::IE_Pressed,this,&ATestCharacter::Fire);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Released, this, &ATestCharacter::StopFire);

	PlayerInputComponent->BindAction(FName("Dash"), EInputEvent::IE_Pressed, this, &ATestCharacter::Dash);
	//PlayerInputComponent->BindAction(FName("Dash"),EInputEvent::IE_Pressed,this,&ATestCharacter::SpawnPoolObject);
	PlayerInputComponent->BindAction(FName("Dash"), EInputEvent::IE_Released, this, &ATestCharacter::WaitToClear);
}


#pragma region Funciones del Movimiento del Jugador

void ATestCharacter::MoveForward(float Value)
{
	if ((Value != 0.0f) && Controller != nullptr)
	{
		FRotator Rotation{ Controller->GetControlRotation() };
		FRotator Yaw{ 0.0f,Rotation.Yaw,0.0f };

		FVector Direction{ FRotationMatrix{Yaw}.GetUnitAxis(EAxis::X) };

		AddMovementInput(Direction * Value);

	}
}

void ATestCharacter::MoveRight(float Value)
{
	if ((Value != 0.0f) && Controller != nullptr)
	{
		FRotator Rotation{ Controller->GetControlRotation() };
		FRotator Yaw{ 0.0f,Rotation.Yaw,0.0f };

		FVector Direction{ FRotationMatrix{Yaw}.GetUnitAxis(EAxis::Y) };

		AddMovementInput(Direction * Value);
	}
}



#pragma endregion


#pragma region Funciones de Acciones (Disparos,etc...)

void ATestCharacter::Fire()
{
	bIsFiring = true;

	if (AWeapon* WP = Cast<AWeapon>(UGameplayStatics::GetActorOfClass(this,AWeapon::StaticClass())))
	{
		WP->StartFire();

		
		
	}

	
}

void ATestCharacter::StopFire()
{
	if (AWeapon* WP = Cast<AWeapon>(UGameplayStatics::GetActorOfClass(this, AWeapon::StaticClass())))
	{
		WP->StopFire();
	}
}


//Spawnear arma en el brazo del player
void ATestCharacter::SpawnWeapon()
{
	
	if (WeaponBlueprint)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.Owner = this;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponBlueprint, GetActorLocation(), GetActorRotation(), SpawnParameters);
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
	}

	
}


void ATestCharacter::Dash()
{
	if (bCanDash)
	{
		bIsDashing = true;
		GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		LaunchCharacter(FVector(GetLastMovementInputVector().X,GetLastMovementInputVector().Y,0.0f).GetSafeNormal() * DashDistance,true,true);
		bCanDash = false;
		GetWorldTimerManager().SetTimer(UnusedHandle,this,&ATestCharacter::StopDash,DashStop,false);
		SpawnPoolObject();
	}
}

void ATestCharacter::StopDash()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->BrakingFrictionFactor = 2.0f;
	GetWorldTimerManager().SetTimer(UnusedHandle,this,&ATestCharacter::ResetDash, DashCooldown,false);
	bIsDashing = false;
}

void ATestCharacter::ResetDash()
{
	bCanDash = true;
}




#pragma endregion



void ATestCharacter::OnHealthChangedComponent(UHealthComponent* OwningHealthComponent, float Health, float HealthDelta, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f && !bDied)
	{
		bDied = true;

		GetCharacterMovement()->StopMovementImmediately();
		/*GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		DetachFromControllerPendingDestroy();

		SetLifeSpan(10.0f);*/

		//SetActorRotation(FRotator(0.0f));

		//DetachFromControllerPendingDestroy();

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		//SetLifeSpan(10.0f);

		//PlayerControllerRef->bEnableMouseOverEvents = false;

		if (PlayerDeathSoundFX)
		{
			UGameplayStatics::PlaySound2D(this, PlayerDeathSoundFX);
		}
		

	}
}


void ATestCharacter::RotateCharacter(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - GetActorLocation();

	FRotator LookRotation = FRotator(0.0f,ToTarget.Rotation().Yaw,0.0f);


	SetActorRotation(LookRotation+ FRotator(0.0f,9.5f,0.0f));

	/*if (GetActorRotation().Yaw < -120.0f)
	{
		SetActorRotation(LookRotation + FRotator(0.0f, -50.0f, 0.0f));
	}
	else {
		SetActorRotation(LookRotation);
	}*/

	

	

}


#pragma region Funciones del Pool Object

float ATestCharacter::GetLifespan()
{
	return UKismetMathLibrary::RandomFloatInRange(LifespanMin, LifespanMax);
}

FVector ATestCharacter::GetRandomPointInVolume()
{
	FVector SpawnOrigin = BoxComponent->Bounds.Origin;
	FVector SpawnExtent = BoxComponent->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin,SpawnExtent);
}

void ATestCharacter::SpawnPoolObject()
{
	APoolableActor* PoolableActor = ComponentPool->GetObjectPool();

	PoolableActor->SetActorLocation(GetActorLocation());
	PoolableActor->SetLifeSpan(GeneralLifeSpan);
	PoolableActor->SetActive(true);
	//PoolableActor->execK2_SetActorRotation()
	PoolableActor->SetActorRotation(GetActorRotation());

	GetWorldTimerManager().SetTimer(SpawnCooldown_TimerHandle,this,&ATestCharacter::SpawnPoolObject,SpawnCooldown,false);
}

void ATestCharacter::ClearSpawnPoolingTime()
{
	GetWorldTimerManager().ClearTimer(SpawnCooldown_TimerHandle);
}

void ATestCharacter::WaitToClear()
{
	GetWorldTimerManager().SetTimer(FinishCooldownHandle, this, &ATestCharacter::ClearSpawnPoolingTime, SpawnCooldown, false);
}

#pragma endregion






