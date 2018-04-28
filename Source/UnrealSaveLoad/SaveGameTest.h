// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameTest.generated.h"

/**
 * 
 */

USTRUCT()
struct  FSaveTestObject
{
    GENERATED_BODY()
    
    UPROPERTY()
    FVector Position;
};

UCLASS()
class UNREALSAVELOAD_API USaveGameTest : public USaveGame
{
	GENERATED_BODY()

	USaveGameTest();

public:
	
    
	UPROPERTY(VisibleAnywhere, Category = Basic)
    FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;
    
    UPROPERTY(VisibleAnywhere, Category = Basic)
    TArray<FSaveTestObject> SaveObjects;
	
	
};
