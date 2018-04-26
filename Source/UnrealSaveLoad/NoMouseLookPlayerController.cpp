// Fill out your copyright notice in the Description page of Project Settings.

#include "NoMouseLookPlayerController.h"

ANoMouseLookPlayerController::ANoMouseLookPlayerController() : APlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bCinemaDisableInputLook = true;
	UE_LOG(LogTemp, Warning, TEXT("ANoMouseLookPlayerController()"));

}

void ANoMouseLookPlayerController::SetupInputComponent()
{
}
