// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Characters/TestCharacter.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{

}


//Funcion para Actualizar las propiedades de las animaciones (velocidad, direccion,etc...)
void UCharacterAnimInstance::BlueprintUpdateProperties(float DeltaTime)
{
	if (ATestCharacter* Character = Cast<ATestCharacter>(TryGetPawnOwner()))
	{
		FVector Velocity = Character->GetVelocity();
		Velocity.Z = 0.0f;
		Speed = Velocity.Size();


		bIsInAir = Character->GetCharacterMovement()->IsFalling();

		if (Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
		{
			bIsAccelerating = true;
		}
		else {
			bIsAccelerating = false;
		}

		FRotator Rotation = Character->GetActorRotation();

		Direction = CalculateDirection(Velocity, Rotation);

		if (Character->bDied == true)
		{
			bDead = true;
		}
	}
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	ATestCharacter* Character = Cast<ATestCharacter>(TryGetPawnOwner());
}
