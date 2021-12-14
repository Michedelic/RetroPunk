// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTrigger1.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ARoomTrigger1::ARoomTrigger1()
{
	
}


void ARoomTrigger1::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	DoorInstance = Cast<ARoomDoor>(UGameplayStatics::GetActorOfClass(this, ARoomDoor::StaticClass()));

	PlayerCharacter = Cast<ATestCharacter>(OtherActor);

	APlayerController* MyController = UGameplayStatics::GetPlayerController(this,0);

	FViewTargetTransitionParams TransitionParams;

	if (PlayerCharacter && MyController)
	{
		
		FVector PlayerLocation = GetTransform().InverseTransformPosition(PlayerCharacter->GetActorLocation());

		USpringArmComponent* SpringTemp = PlayerCharacter->GetBoomCamera();

		SpringTemp->SetActive(false);

		DoorInstance->SetActorHiddenInGame(false);
		DoorInstance->SetActorEnableCollision(true);
		DoorInstance->DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		DoorInstance->DoorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		if (CurrentCamera)
		{
			MyController->SetViewTarget(CurrentCamera, TransitionParams);
		}
		
	}


}

void ARoomTrigger1::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	PlayerCharacter = Cast<ATestCharacter>(OtherActor);


	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);

	FViewTargetTransitionParams TransitionParams;

	if (PlayerCharacter && MyController)
	{
		USpringArmComponent* SpringTemp = PlayerCharacter->GetBoomCamera();

		SpringTemp->SetActive(true);

		
		
		/*MyController->SetViewTarget(PlayerCharacter, TransitionParams);*/

		if (PreviousCamera)
		{
			MyController->SetViewTarget(PreviousCamera, TransitionParams);
		}
		

	}
}
