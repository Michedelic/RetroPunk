// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugHUD.h"
#include "UObject/ConstructorHelpers.h"

ADebugHUD::ADebugHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/Roboto"));

	MainFont = Font.Object;
	MainFont->LegacyFontSize = 13.0f;
}

