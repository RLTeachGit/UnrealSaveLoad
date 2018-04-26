// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NoMouseLookPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSAVELOAD_API ANoMouseLookPlayerController : public APlayerController
{
	GENERATED_BODY()

	ANoMouseLookPlayerController();

	virtual void SetupInputComponent();
	
	
};
