// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BasicSaveGame.generated.h"

/**
 * 
 */

USTRUCT()
struct  FBasicSaveObject
{
	GENERATED_BODY()

		UPROPERTY()
		FVector Position;
};


UCLASS()
class UNREALSAVELOAD_API UBasicSaveGame : public USaveGame
{
	GENERATED_BODY()
	UBasicSaveGame();

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FBasicSaveObject> SaveObjects;

};
