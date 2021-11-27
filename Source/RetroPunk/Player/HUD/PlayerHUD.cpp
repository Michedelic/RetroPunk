// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "../Characters/TestCharacter.h"
#include "../Components/HealthComponent.h"
#include "../../AI/Pawns/BotEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


APlayerHUD::APlayerHUD()
{

}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();


	UHealthComponent* health = Cast<UHealthComponent>(UGameplayStatics::GetObjectClass(UHealthComponent::StaticClass()));
	ABotEnemy* bot = Cast<ABotEnemy>(UGameplayStatics::GetActorOfClass(this,ABotEnemy::StaticClass()));

	if (ATestCharacter* player = Cast<ATestCharacter>(GetOwningPawn()))
	{
		AddFloat(L"Max Speed: ",player->GetMovementComponent()->GetMaxSpeed());
		AddFloat(L"Player Life: ",player->HealthComponent->CurrentHealth);
		//AddFloat(L"Bot Health: ",bot->CurrentBotHealth);
		//AddFloat(L"Health: ",health->CurrentHealth);
		//AddFloat(L"Dash Timer: ", player->DashStop);
	}
}