// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class   UBasicSaveLoad;

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NoMouseLookPlayerController.h"
#include "StaticPawn.h"
#include "SpawnableActor.h"
#include "Engine/World.h"

#include "SaveGameTest.h"
#include "Kismet/GameplayStatics.h"

#include "BasicSaveLoad.h"

#include "SaveLoadTestGamemode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSAVELOAD_API ASaveLoadTestGamemode : public AGameMode
{
	GENERATED_BODY()
	ASaveLoadTestGamemode();

public:
	UFUNCTION(BlueprintCallable)
	void	SpawnObjectTest();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpawnableActor> mBaseObject;
	

	void	OnSpawnableActorDestroy(ASpawnableActor* vActor);

    
	UFUNCTION(BlueprintCallable)
	ASpawnableActor* SpawnMyActor(const FVector& Position,const FRotator& Rotation);

    
	UFUNCTION(BlueprintCallable)
	void	SaveMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    LoadMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    ClearMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    TestLoad();
    
    UFUNCTION(BlueprintCallable)
    void    TestSave();

    UPROPERTY()
    UBasicSaveLoad*  SaveLoadGame;


public:
	TArray<ASpawnableActor*>	mActorArray;


private: //Spawn Range
	float	XMin = -200.0;
	float	XMax = 200.0;
	float	YMin = -200.0;
	float	YMax = 200.0;
	float	ZMin = 70.0;
	float	ZMax = 200.0;

};
