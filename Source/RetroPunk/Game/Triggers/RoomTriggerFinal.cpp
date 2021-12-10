// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomTriggerFinal.h"


ARoomTriggerFinal::ARoomTriggerFinal()
{

}




void ARoomTriggerFinal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayerCharacter = Cast<ATestCharacter>(OtherActor);

	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);

	FViewTargetTransitionParams TransitionParams;

	if (PlayerCharacter && MyController)
	{

		FVector PlayerLocation = GetTransform().InverseTransformPosition(PlayerCharacter->GetActorLocation());

		USpringArmComponent* SpringTemp = PlayerCharacter->GetBoomCamera();

		SpringTemp->SetActive(false);

		if (FinalCamera)
		{
			MyController->SetViewTarget(FinalCamera, TransitionParams);
		}

	}
}

void ARoomTriggerFinal::NotifyActorEndOverlap(AActor* OtherActor)
{

	Super::NotifyActorEndOverlap(OtherActor);

	PlayerCharacter = Cast<ATestCharacter>(OtherActor);


	APlayerController* MyController = UGameplayStatics::GetPlayerController(this, 0);

	FViewTargetTransitionParams TransitionParams;

	if (PlayerCharacter && MyController)
	{
		USpringArmComponent* SpringTemp = PlayerCharacter->GetBoomCamera();

		SpringTemp->SetActive(true);



		MyController->SetViewTarget(PlayerCharacter, TransitionParams);

		


	}
}
