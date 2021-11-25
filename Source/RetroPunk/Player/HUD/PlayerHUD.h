// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DebugHUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API APlayerHUD : public ADebugHUD
{
	GENERATED_BODY()

public:

	APlayerHUD();

	virtual void DrawHUD() override;
	
};
