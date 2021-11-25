// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UCharacterAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "Player")
		void BlueprintUpdateProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Speed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		bool bIsAccelerating = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		bool bIsInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		float Direction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
		bool bDead = false;
	
};
