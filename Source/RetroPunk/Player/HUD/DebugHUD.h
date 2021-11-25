// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "CanvasItem.h"
#include "DebugHUD.generated.h"

/**
 * 
 */
UCLASS()
class RETROPUNK_API ADebugHUD : public AHUD
{
	GENERATED_BODY()

public:

	ADebugHUD();


	void AddText(const TCHAR* title, const FText& value)
	{
		RenderStatistics(title,value);
	}

	void AddFloat(const TCHAR* title, float value)
	{
		RenderStatistics(title,FText::AsNumber(value),(value > 0.0f) ? FLinearColor::Green : FLinearColor::Red);
	}


	void AddInt(const TCHAR* title,int32 value)
	{
		RenderStatistics(title,FText::AsNumber(value));
	}

	void AddBool(const TCHAR* title, bool value)
	{
		RenderStatistics(title,CBoolToText(value),(value == true) ? FLinearColor::Green : FLinearColor::Red);
	}

	virtual void DrawHUD() override
	{
		X = Y = 50.0f;
	}





private:
	
	FText CStringToText(const TCHAR* value)
	{
		return FText::FromString(value);
	}


	FText CBoolToText(bool value)
	{
		return CStringToText((value == true) ? TEXT("True") : TEXT("False"));
	}

	void RenderStatistics(const TCHAR* title, const FText& value, const FLinearColor& color = FLinearColor::White)
	{
		FCanvasTextItem item0(FVector2D(X,Y),CStringToText(title),MainFont,FLinearColor::White);
		item0.EnableShadow(FVector(0.0f,0.0f,0.0f));
		Canvas->DrawItem(item0);

		FCanvasTextItem item1(FVector2D(X + horizontalOffset,Y),value,MainFont,color);
		item1.EnableShadow(FVector::ZeroVector);
		Canvas->DrawItem(item1);

		Y += lineHeight;

	}
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Player,meta=(AllowPrivateAccess=true))
	float X = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = true))
	float Y = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = true))
		float horizontalOffset = 105.0f;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player, meta = (AllowPrivateAccess = true))
		float lineHeight = 15.0f;

	UPROPERTY(Transient)
	UFont*  MainFont;

};
